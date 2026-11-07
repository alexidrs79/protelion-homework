#pragma once
#include <chrono>
 
// internal class for stopwatch functionality
// the start time is saved when the object is created.

class Stopwatch {
public:
    Stopwatch();
    int getElapsedSecond() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
};