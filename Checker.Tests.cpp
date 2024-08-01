// Checker.Tests.cpp
#include <gtest/gtest.h>
#include "Checker.h"

// Test overall battery status
TEST(BatteryTest, TestBatteryIsOk) {
    EXPECT_TRUE(batteryIsOk(25, 70, 0.5));
    EXPECT_FALSE(batteryIsOk(50, 70, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 10, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 70, 0.9));
    EXPECT_TRUE(batteryIsOk(2.25, 24, 0.76));
}

