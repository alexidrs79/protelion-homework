#include "timer.h"
#include "stopwatch.h"
#include <memory>

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