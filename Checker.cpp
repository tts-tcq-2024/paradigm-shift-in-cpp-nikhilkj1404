#include "Checker.h"
#include <iostream>

// Constant definitions for parameter ranges
const BreachRange TEMPERATURE_BREACH_RANGE = {0, 45};
const WarningRange TEMPERATURE_WARNING_RANGE = {0 + 45 * 0.05, 45 - 45 * 0.05};

const BreachRange SOC_BREACH_RANGE = {20, 80};
const WarningRange SOC_WARNING_RANGE = {20 + 80 * 0.05, 80 - 80 * 0.05};

const BreachRange CHARGE_RATE_BREACH_RANGE = {0, 0.8};
const WarningRange CHARGE_RATE_WARNING_RANGE = {0 + 0.8 * 0.05, 0.8 - 0.8 * 0.05};

// Function to determine warning status based on value and warning range
WarningStatus getWarningStatus(float value, const WarningRange& range) {
    if (value < range.lowWarning) {
        return LOW_WARNING;
    }
    if (value >= range.highWarning) {
        return HIGH_WARNING;
    }
    return NO_WARNING;
}

// Function to determine breach status based on value and breach range
BreachStatus getBreachStatus(float value, const BreachRange& range) {
    if (value < range.lowBreach) {
        return LOW_BREACH;
    }
    if (value >= range.highBreach) {
        return HIGH_BREACH;
    }
    return NO_BREACH; 
}

// Function to determine parameter status based on value, breach, and warning ranges
ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange) {
    BreachStatus breachStatus = getBreachStatus(value, breachRange);
    if (breachStatus != NO_BREACH) {
        return static_cast<ParameterStatus>(breachStatus);
    }

    WarningStatus warningStatus = getWarningStatus(value, warningRange);
    if (warningStatus != NO_WARNING) {
        return static_cast<ParameterStatus>(warningStatus);
    }

    return NORMAL;
}

// Function to get a warning message based on the warning status
std::string getWarningMessage(const std::string& parameter, WarningStatus warningStatus) {
    if (warningStatus == LOW_WARNING) {
        return "Warning: " + parameter + " is approaching discharge.";
    }
    if (warningStatus == HIGH_WARNING) {
        return "Warning: " + parameter + " is approaching charge-peak.";
    }
    return "";
}

// Function to get a breach message based on the breach status
std::string getBreachMessage(const std::string& parameter, BreachStatus breachStatus) {
    if (breachStatus == LOW_BREACH) {
        return parameter + " is below the safe range!";
    }
    if (breachStatus == HIGH_BREACH) {
        return parameter + " is above the safe range!";
    }
    return "";
}

// Function to translate a parameter status into a message
std::string statusToMessageTranslation(const std::string& parameter, ParameterStatus parameterStatus) {
    if (parameterStatus == NORMAL) {
        return parameter + " is normal.";
    }

    BreachStatus breachStatus = static_cast<BreachStatus>(parameterStatus);
    std::string message = getBreachMessage(parameter, breachStatus);
    if (!message.empty()) {
        return message;
    }

    WarningStatus warningStatus = static_cast<WarningStatus>(parameterStatus);
    message = getWarningMessage(parameter, warningStatus);
    return message;
}

// Function to check if temperature is within acceptable range
bool checkTemperature(float temperature) {
    ParameterStatus status = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to check if state of charge is within acceptable range
bool checkSoc(float soc) {
    ParameterStatus status = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to check if charge rate is within acceptable range
bool checkChargeRate(float chargeRate) {
    ParameterStatus status = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to determine overall battery health
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    // Get status for each parameter
    ParameterStatus tempStatus = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    ParameterStatus socStatus = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    ParameterStatus chargeRateStatus = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);

    // Output the status message for each parameter
    std::cout << statusToMessageTranslation("Temperature", tempStatus) << std::endl;
    std::cout << statusToMessageTranslation("State of Charge", socStatus) << std::endl;
    std::cout << statusToMessageTranslation("Charge Rate", chargeRateStatus) << std::endl;

    // Determine if each parameter is OK (not in breach)
    bool tempOk = tempStatus != LOW_BREACH && tempStatus != HIGH_BREACH;
    bool socOk = socStatus != LOW_BREACH && socStatus != HIGH_BREACH;
    bool chargeRateOk = chargeRateStatus != LOW_BREACH && chargeRateStatus != HIGH_BREACH;

    // Return true if all parameters are OK
    return tempOk && socOk && chargeRateOk;
}

