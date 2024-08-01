// Checker.cpp
#include "Checker.h"
#include <iostream>


const BreachRange TEMPERATURE_BREACH_RANGE = {0, 45};
const WarningRange TEMPERATURE_WARNING_RANGE = {0 + 45 * 0.05, 45 - 45 * 0.05};

const BreachRange SOC_BREACH_RANGE = {20, 80};
const WarningRange SOC_WARNING_RANGE = {20 + 80 * 0.05, 80 - 80 * 0.05};

const BreachRange CHARGE_RATE_BREACH_RANGE = {0, 0.8};
const WarningRange CHARGE_RATE_WARNING_RANGE = {0 + 0.8 * 0.05, 0.8 - 0.8 * 0.05};

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


std::string getWarningMessage(const std::string& parameter, ParameterStatus warningStatus) {
    if (warningStatus == LOW_WARNING) {
        return "Warning: " + parameter + " is approaching discharge.";
    }
    if (warningStatus == HIGH_WARNING) {
        return "Warning: " + parameter + " is approaching charge-peak.";
    }
    return "";
}

std::string getBreachMessage(const std::string& parameter, ParameterStatus breachStatus) {
    if (breachStatus == LOW_BREACH) {
        return parameter + " is below the safe range!";
    }
    if (breachStatus == HIGH_BREACH) {
        return parameter + " is above the safe range!";
    }
    return "";
}

std::string statusToMessageTranslation(const std::string& parameter, ParameterStatus parameterStatus) {
    std::string message = getWarningMessage(parameter, parameterStatus);
    if (message.empty()) {
        message = getBreachMessage(parameter, parameterStatus);
    }
    if (message.empty()) {
        message = parameter + " is normal.";
    }
    return message;
}


bool checkTemperature(float temperature) {
    ParameterStatus status = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    return status;
}

bool checkSoc(float soc) {
    ParameterStatus status = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    return status;
}


bool checkChargeRate(float chargeRate) {
    ParameterStatus status = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);
    return status;
}


bool batteryIsOk(float temperature, float soc, float chargeRate) {
    
    ParameterStatus tempStatus = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    ParameterStatus socStatus = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    ParameterStatus chargeRateStatus = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);
    
    bool tempOk = checkTemperature(temperature);
    bool socOk = checkSoc(soc);
    bool chargeRateOk = checkChargeRate(chargeRate);

    
    std::cout << statusToMessageTranslation("Temperature", tempStatus) << std::endl;
    std::cout << statusToMessageTranslation("State of Charge", socStatus) << std::endl;
    std::cout << statusToMessageTranslation("Charge Rate", chargeRateStatus) << std::endl;

    return tempOk && socOk && chargeRateOk;
}
