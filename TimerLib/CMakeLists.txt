cmake_minimum_required(VERSION 3.16)
project(TimerLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build TimerLib as a dynamic library" OFF)

add_library(TimerLib 
src/stopwatch.cpp
src/timer.cpp
)

target_include_directories(TimerLib
PUBLIC include
PRIVATE src)

option(TIMERLIB_BUILD_TESTS "Build the unit tests" OFF)

if(TIMERLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
    endif()
