#include "stopwatch.h"

Stopwatch::Stopwatch() {
    start_time = std::chrono::steady_clock::now();
}

int Stopwatch::getElapsedSecond() const {
    auto now = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
    return (int)seconds.count(); 
}