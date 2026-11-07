#include "timer.h"
#include "stopwatch.h"
#include <memory>

// Implements start() and stop() using one Stopwatch held in a unique_ptr.
// start() creates a new Stopwatch (replacing any running one),
// stop() reads the elapsed time and destroys it.
// Not thread-safe: intended to be called from one thread.

static std::unique_ptr<Stopwatch> currentStopwatch;

int start() {
    currentStopwatch = std::make_unique<Stopwatch>();
    return 0;
}

int stop() {
   if (currentStopwatch == nullptr) {
        return -1; // No stopwatch is running
    }
    int seconds = currentStopwatch->getElapsedSecond();
    currentStopwatch.reset(); // Deletes the stopwatch
    return seconds;
}