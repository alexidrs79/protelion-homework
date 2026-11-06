#!/bin/bash
set -e

cd "$(dirname "$0")"

rm -rf build/ios-device build/ios-simulator build/TimerLib.xcframework

cmake -S . -B build/ios-device \
-DCMAKE_SYSTEM_NAME=iOS \
-DCMAKE_OSX_ARCHITECTURES=arm64 \
-DCMAKE_OSX_DEPLOYMENT_TARGET=17 \
-DCMAKE_OSX_SYSROOT=iphoneos \
-DCMAKE_BUILD_TYPE=Release
cmake --build build/ios-device 

cmake -S . -B build/ios-simulator \
-DCMAKE_SYSTEM_NAME=iOS \
"-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64" \
-DCMAKE_OSX_DEPLOYMENT_TARGET=17 \
-DCMAKE_OSX_SYSROOT=iphonesimulator \
-DCMAKE_BUILD_TYPE=Release
cmake --build build/ios-simulator

xcodebuild -create-xcframework \
-library build/ios-device/libTimerLib.a -headers include \
-library build/ios-simulator/libTimerLib.a -headers include \
-output build/TimerLib.xcframework