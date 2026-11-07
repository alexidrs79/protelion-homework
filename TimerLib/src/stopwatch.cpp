#include "stopwatch.h"

// Uses steady_clock so the result isn't affected by changes to the system time.
// Elapsed time is rounded down to whole seconds.

Stopwatch::Stopwatch() {
    start_time = std::chrono::steady_clock::now();
}

int Stopwatch::getElapsedSecond() const {
    auto now = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
    return (int)seconds.count(); 
}