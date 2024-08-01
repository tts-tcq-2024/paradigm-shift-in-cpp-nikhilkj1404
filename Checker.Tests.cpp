// Checker.Tests.cpp
#include <gtest/gtest.h>
#include "Checker.h"

TEST(BatteryTest, NormalConditions) {
    EXPECT_TRUE(batteryIsOk(25.0, 50.0, 0.5));
}

TEST(BatteryTest, LowWarningConditions) {
    EXPECT_TRUE(batteryIsOk(0 + 45 * 0.05 + 0.1, 50.0, 0.5));
    EXPECT_TRUE(batteryIsOk(25.0, 20 + 80 * 0.05 + 1, 0.5));
    EXPECT_TRUE(batteryIsOk(25.0, 50.0, 0.8 - 0.8 * 0.05 - 0.01));
}

TEST(BatteryTest, HighWarningConditions) {
    EXPECT_TRUE(batteryIsOk(45 - 45 * 0.05 - 0.1, 50.0, 0.5));
    EXPECT_TRUE(batteryIsOk(25.0, 80 - 80 * 0.05 - 1, 0.5));
    EXPECT_TRUE(batteryIsOk(25.0, 50.0, 0.8 - 0.8 * 0.05 - 0.01));
}

TEST(BatteryTest, LowBreachConditions) {
    EXPECT_FALSE(batteryIsOk(-1.0, 50.0, 0.5));
    EXPECT_FALSE(batteryIsOk(25.0, 10.0, 0.5));
    EXPECT_FALSE(batteryIsOk(25.0, 50.0, -0.1));
}

TEST(BatteryTest, HighBreachConditions) {
    EXPECT_FALSE(batteryIsOk(46.0, 50.0, 0.5));
    EXPECT_FALSE(batteryIsOk(25.0, 90.0, 0.5));
    EXPECT_FALSE(batteryIsOk(25.0, 50.0, 1.0));
}

