// Checker.h
#ifndef CHECKER_H
#define CHECKER_H

#include <string>


enum WarningStatus {
    NO_WARNING,
    LOW_WARNING,
    HIGH_WARNING
};


enum BreachStatus {
    NO_BREACH,
    LOW_BREACH,
    HIGH_BREACH
};


enum ParameterStatus {
    NORMAL,
    LOW_WARNING,
    HIGH_WARNING,
    LOW_BREACH,
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


WarningStatus getWarningStatus(float value, const WarningRange& range);
BreachStatus getBreachStatus(float value, const BreachRange& range);
ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange);
std::string statusToMessageTranslation(const std::string& parameter, ParameterStatus parameterStatus);
bool batteryIsOk(float temperature, float soc, float chargeRate);

#endif // CHECKER_H
