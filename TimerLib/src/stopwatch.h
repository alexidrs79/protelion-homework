#pragma once
#include <chrono>
 
class Stopwatch {
public:
    Stopwatch();
    int getElapsedSecond() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;
};