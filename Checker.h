// Checker.h
#ifndef CHECKER_H
#define CHECKER_H

#include <string>


enum ParameterStatus {
    LOW_BREACH,
    LOW_WARNING,
    NORMAL,
    HIGH_WARNING,
    HIGH_BREACH
};


struct BreachRange {
    float lowBreach;
    float highBreach;
};


struct WarningRange {
    float lowWarning;
    float highWarning;
};

BreachStatus getBreachStatus(float value, const BreachRange& range);
WarningStatus getWarningStatus(float value, const WarningRange& range);
ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange);
std::string translateStatusToMessage(const std::string& parameter, ParameterStatus status);

bool checkTemperature(float temperature);
bool checkSoc(float soc);
bool checkChargeRate(float chargeRate);
bool batteryIsOk(float temperature, float soc, float chargeRate);

#endif
