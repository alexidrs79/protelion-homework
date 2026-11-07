#include "timer.h"
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

// GoogleTest unit tests for start() and stop().
// SetUp() calls stop() so every test starts with no running timer.

static void waitMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

class TimerTest : public ::testing::Test {
protected:
void SetUp() override {
    stop();
}
};

TEST_F(TimerTest, StartReturnsZero) {
    EXPECT_EQ(start(), 0);
}

TEST_F(TimerTest, StopRightAfterStartReturnsZero) {
    start();
    EXPECT_EQ(stop(), 0);
}

TEST_F(TimerTest, StopReturnsWholeSeconds) {
    start();
    waitMs(1200);
    EXPECT_EQ(stop(), 1);
}

TEST_F(TimerTest, StopWithoutStartReturnsMinusOne) {
    EXPECT_EQ(stop(), -1);
}

TEST_F(TimerTest, StopTwiceReturnsMinusOneSecondTime) {
    start();
    stop();
    EXPECT_EQ(stop(), -1);
}

TEST_F(TimerTest, StartTwiceRestartsTimer) {
    start();
    waitMs(1200);
    start();
    EXPECT_EQ(stop(), 0);

}