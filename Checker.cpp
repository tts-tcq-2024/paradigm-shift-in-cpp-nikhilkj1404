// Checker.cpp
#include "Checker.h"
#include <iostream>


const BreachRange TEMPERATURE_BREACH_RANGE = {0, 45};
const WarningRange TEMPERATURE_WARNING_RANGE = {0 + 45 * 0.05, 45 - 45 * 0.05};

const BreachRange SOC_BREACH_RANGE = {20, 80};
const WarningRange SOC_WARNING_RANGE = {20 + 80 * 0.05, 80 - 80 * 0.05};

const BreachRange CHARGE_RATE_BREACH_RANGE = {0, 0.8};
const WarningRange CHARGE_RATE_WARNING_RANGE = {0, 0.8 - 0.8 * 0.05};

ParameterStatus getWarningStatus(float value, const WarningRange& range) {
    if (value < range.lowWarning) {
        return LOW_WARNING;
    }
    if (value >= range.highWarning) {
        return HIGH_WARNING;
    }
    return NORMAL;
}

ParameterStatus getBreachStatus(float value, const BreachRange& range) {
    if (value < range.lowBreach) {
        return LOW_BREACH;
    }
    if (value >= range.highBreach) {
        return HIGH_BREACH;
    }
    return NORMAL;
}


ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange) {
    ParameterStatus warningStatus = getWarningStatus(value, warningRange);
    if (warningStatus != NORMAL) {
        return warningStatus;
    }
    return getBreachStatus(value, breachRange);
}


std::string translateStatusToMessage(const std::string& parameter, ParameterStatus status) {
    static const std::string messages[] = {
        parameter + " is below the safe range!",
        "Warning: " + parameter + " is approaching discharge.",
        parameter + " is normal.",
        "Warning: " + parameter + " is approaching charge-peak.",
        parameter + " is above the safe range!"
    };

    if (status < LOW_BREACH || status > HIGH_BREACH) {
        return "Unknown status for " + parameter;
    }

    return messages[status];
}

/
bool checkTemperature(float temperature) {
    ParameterStatus status = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}

bool checkSoc(float soc) {
    ParameterStatus status = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}

/
bool checkChargeRate(float chargeRate) {
    ParameterStatus status = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}


bool batteryIsOk(float temperature, float soc, float chargeRate) {
    
    ParameterStatus tempStatus = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    ParameterStatus socStatus = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    ParameterStatus chargeRateStatus = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);

    
    std::cout << translateStatusToMessage("Temperature", tempStatus) << std::endl;
    std::cout << translateStatusToMessage("State of Charge", socStatus) << std::endl;
    std::cout << translateStatusToMessage("Charge Rate", chargeRateStatus) << std::endl;

    
    bool tempOk = (tempStatus != LOW_BREACH && tempStatus != HIGH_BREACH);
    bool socOk = (socStatus != LOW_BREACH && socStatus != HIGH_BREACH);
    bool chargeRateOk = (chargeRateStatus != LOW_BREACH && chargeRateStatus != HIGH_BREACH);

    
    return tempOk && socOk && chargeRateOk;
}
