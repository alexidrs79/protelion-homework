include(FetchContent)

# Downloads GoogleTest and builds the TimerLibTests executable.

FetchContent_Declare(
    googletest 
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(TimerLibTests timer_tests.cpp)
target_link_libraries(TimerLibTests PRIVATE TimerLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TimerLibTests)
