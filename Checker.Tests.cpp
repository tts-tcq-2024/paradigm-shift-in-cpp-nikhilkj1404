// Checker.Tests.cpp
#include <gtest/gtest.h>
#include "Checker.h"

// Test temperature checks
TEST(BatteryTest, TestTemperature) {
    EXPECT_TRUE(checkTemperature(25));
    EXPECT_FALSE(checkTemperature(-1));
    EXPECT_FALSE(checkTemperature(50));
    EXPECT_TRUE(checkTemperature(2.25));
    EXPECT_TRUE(checkTemperature(42.75));
}

// Test state of charge (SoC) checks
TEST(BatteryTest, TestStateOfCharge) {
    EXPECT_TRUE(checkSoc(70));
    EXPECT_FALSE(checkSoc(10));
    EXPECT_FALSE(checkSoc(90));
    EXPECT_TRUE(checkSoc(24));
    EXPECT_TRUE(checkSoc(76));
}

// Test charge rate checks
TEST(BatteryTest, TestChargeRate) {
    EXPECT_TRUE(checkChargeRate(0.5));
    EXPECT_FALSE(checkChargeRate(-0.1));
    EXPECT_FALSE(checkChargeRate(0.9));
    EXPECT_TRUE(checkChargeRate(0.76));
}

// Test overall battery status
TEST(BatteryTest, TestBatteryIsOk) {
    EXPECT_TRUE(batteryIsOk(25, 70, 0.5));
    EXPECT_FALSE(batteryIsOk(50, 70, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 10, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 70, 0.9));
    EXPECT_TRUE(batteryIsOk(2.25, 24, 0.76));
}

