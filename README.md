# Protelion iOS Assignment – Timer

A small iOS app with one button. START starts a timer in a C++ library, STOP stops it and shows how many whole seconds have passed. The project has three separate parts: a C++ library, an Objective-C++ wrapper and a SwiftUI app.

## Requirements

- macOS with **Xcode 27.2** or newer (the project uses Xcode 27's JSON project format)
- **iOS 17.6** or newer on the simulator or device
- **CMake 3.16** or newer (`brew install cmake`)
- Xcode set as the active developer directory:
  ```bash
  sudo xcode-select -s /Applications/Xcode.app/Contents/Developer
  ```
- Internet access the first time the unit tests are built (CMake downloads GoogleTest 1.17.0)

> **Run `TimerLib/build_ios.sh` before opening Xcode.** The XCFramework is a build output and isn't in the repo, so the project won't build without it.

## Project structure

```
protelion-homework/
├── TimerLib/                 C++ library
│   ├── CMakeLists.txt        static or dynamic build
│   ├── build_ios.sh          builds TimerLib.xcframework (device + simulator)
│   ├── include/timer.h       public API: start() / stop()
│   ├── src/stopwatch.h/.cpp  internal class that measures time
│   ├── src/timer.cpp         start() / stop() implementation
│   └── tests/                GoogleTest unit tests
├── TimerWrapper/             Objective-C++ wrapper (TimerWrapper.framework)
│   ├── TimerWrapper.h        Objective-C interface for Swift
│   └── TimerWrapper.mm       forwards calls to the C++ library
└── TimerApp/                 Xcode project
    ├── TimerApp.xcodeproj    targets: TimerApp and TimerWrapper
    └── TimerApp/             SwiftUI sources
```

## Building the C++ library

Run these from the `TimerLib` folder.

Static library (`libTimerLib.a`):
```bash
cmake -S . -B build/static
cmake --build build/static
```

Dynamic library (`libTimerLib.dylib`):
```bash
cmake -S . -B build/shared -DBUILD_SHARED_LIBS=ON
cmake --build build/shared
```

Unit tests:
```bash
cmake -S . -B build/tests -DTIMERLIB_BUILD_TESTS=ON
cmake --build build/tests
ctest --test-dir build/tests --output-on-failure
```

There are six tests: `start()` returns 0, `stop()` right after `start()` returns 0, 1.2 seconds returns 1, `stop()` without `start()` returns -1, a second `stop()` returns -1, and calling `start()` twice restarts the timer.

## Running the iOS app

1. Build the library for iOS (once, before opening Xcode):
   ```bash
   ./TimerLib/build_ios.sh
   ```
   This creates `TimerLib/build/TimerLib.xcframework` with a device slice (arm64) and a simulator slice (arm64 + x86_64).
2. Open `TimerApp/TimerApp.xcodeproj`.
3. Select the **TimerApp** scheme and an iPhone simulator, then press **Cmd+R**.

To run on a real iPhone, pick your own team under *Signing & Capabilities* for both targets.

## Technical decisions

**C++ library**
- Time is measured by a separate `Stopwatch` class that saves `std::chrono::steady_clock::now()` when it is created. `steady_clock` is used because it does not jump if the device time changes.
- The `Stopwatch` is held in a `std::unique_ptr`. `start()` creates it and `stop()` destroys it with `reset()`, so there is no manual `new`/`delete` to leak.
- The pointer is `static` in `timer.cpp`, so only `start()` and `stop()` can reach it. `Stopwatch` is not in the public header.
- `start()` while already running restarts the timer (the old object is destroyed).
- `stop()` without a running timer returns **-1**. A real duration can't be negative, so it can't be mixed up with a result.
- Seconds are rounded down (`duration_cast<seconds>`).
- Static and dynamic builds both use CMake's standard `BUILD_SHARED_LIBS` option.

**Building for iOS**
- Device and simulator are different platforms, so the library is built twice and packaged as an XCFramework. Xcode picks the right slice.

**Objective-C++ wrapper**
- The wrapper is its own framework target. `TimerLib.xcframework` is linked into it as a static library, so the C++ code ends up inside the wrapper binary.
- `TimerWrapper.h` is plain Objective-C because Swift imports it. All C++ stays in `TimerWrapper.mm`.
- The wrapper only forwards calls. All timing happens in C++.

**Swift integration**
- Swift uses `import TimerWrapper` instead of a bridging header. The wrapper is a separate framework with *Defines Module* on, so importing it as a module is the right mechanism here.

**Swift app**
- SwiftUI, since it's one screen with simple state.
- Portrait and landscape are enabled in the target settings, and the button is centred so it works in both.
- The button only goes back to START after OK is tapped on the alert.
- Both return values are checked: if `start()` isn't 0 or `stop()` returns -1, an error message is shown instead of leaving the UI in the wrong state.

**Deployment target**
- The library (`build_ios.sh`), the wrapper and the app all target iOS 17.0. Using the same version in all three avoids linker warnings about objects built for a newer iOS than the app.
- iOS 17.6 is a recent baseline that still covers most devices. The SwiftUI APIs the app uses are available from iOS 15, so the target could go lower if older devices need support.
- Any iOS 17+ simulator works, including the iOS 27 simulators that come with Xcode 27.

## Known limitations

- **Not thread-safe.** The timer is one global object. Button taps run on the main thread so it's fine here, but calling from several threads would need a mutex.
- **One timer at a time.** The `int start(); int stop();` API can't identify more than one timer.
- **Device sleep.** On Apple platforms `steady_clock` may not count time while the device sleeps, so a measurement across a locked phone can be shorter than real time.
- **The XCFramework isn't in the repo.** It's a build product, so `build_ios.sh` has to be run first.
- **No Mac Catalyst.** The library is only built for iOS and the iOS Simulator.
