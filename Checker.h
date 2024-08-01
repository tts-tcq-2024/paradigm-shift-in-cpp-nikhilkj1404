// Checker.h
#ifndef CHECKER_H
#define CHECKER_H

#include <string>


enum BreachStatus {
    NO_BREACH,
    LOW_BREACH,
    HIGH_BREACH
};

enum WarningStatus {
    NO_WARNING,
    LOW_WARNING,
    HIGH_WARNING
};

struct ParameterRange {
    float lowBreach;
    float lowWarning;
    float highWarning;
    float highBreach;
};

BreachStatus getBreachStatus(float value, const BreachRange& range);
WarningStatus getWarningStatus(float value, const WarningRange& range);
ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange);
std::string statusToMessageTranslation(const std::string& parameter, ParameterStatus parameterStatus)

bool checkTemperature(float temperature);
bool checkSoc(float soc);
bool checkChargeRate(float chargeRate);
bool batteryIsOk(float temperature, float soc, float chargeRate);

#endif
