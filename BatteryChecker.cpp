#include "Checker.h"
#include <iostream>


const BreachRange TEMPERATURE_BREACH_RANGE = {0, 45};
const WarningRange TEMPERATURE_WARNING_RANGE = {0 + 45 * 0.05, 45 - 45 * 0.05};

const BreachRange SOC_BREACH_RANGE = {20, 80};
const WarningRange SOC_WARNING_RANGE = {20 + 80 * 0.05, 80 - 80 * 0.05};

const BreachRange CHARGE_RATE_BREACH_RANGE = {0, 0.8};
const WarningRange CHARGE_RATE_WARNING_RANGE = {0 + 0.8 * 0.05, 0.8 - 0.8 * 0.05};


WarningStatus getWarningStatus(float value, const WarningRange& range) {
    if (value < range.lowWarning) {
        return WarningStatus::LOW_WARNING;
    }
    if (value >= range.highWarning) {
        return WarningStatus::HIGH_WARNING;
    }
    return WarningStatus::NO_WARNING;
}


BreachStatus getBreachStatus(float value, const BreachRange& range) {
    if (value < range.lowBreach) {
        return BreachStatus::LOW_BREACH;
    }
    if (value >= range.highBreach) {
        return BreachStatus::HIGH_BREACH;
    }
    return BreachStatus::NO_BREACH;
}

ParameterStatus getParameterStatus(float value, const BreachRange& breachRange, const WarningRange& warningRange) {
    BreachStatus breachStatus = getBreachStatus(value, breachRange);
    if (breachStatus != BreachStatus::NO_BREACH) {
        return static_cast<ParameterStatus>(breachStatus);
    }

    WarningStatus warningStatus = getWarningStatus(value, warningRange);
    if (warningStatus != WarningStatus::NO_WARNING) {
        return static_cast<ParameterStatus>(warningStatus);
    }

    return ParameterStatus::NORMAL;
}


std::string getWarningMessage(const std::string& parameter, WarningStatus warningStatus) {
    if (warningStatus == WarningStatus::LOW_WARNING) {
        return "Warning: " + parameter + " is approaching discharge.";
    }
    if (warningStatus == WarningStatus::HIGH_WARNING) {
        return "Warning: " + parameter + " is approaching charge-peak.";
    }
    return "";
}


std::string getBreachMessage(const std::string& parameter, BreachStatus breachStatus) {
    if (breachStatus == BreachStatus::LOW_BREACH) {
        return parameter + " is below the safe range!";
    }
    if (breachStatus == BreachStatus::HIGH_BREACH) {
        return parameter + " is above the safe range!";
    }
    return "";
}


std::string statusToMessageTranslation(const std::string& parameter, ParameterStatus parameterStatus) {
    if (parameterStatus == ParameterStatus::NORMAL) {
        return parameter + " is normal.";
    }

    std::string message = getWarningMessage(parameter, static_cast<WarningStatus>(parameterStatus));
    if (!message.empty()) {
        return message;
    }

    message = getBreachMessage(parameter, static_cast<BreachStatus>(parameterStatus));
    return message;
}


bool checkTemperature(float temperature) {
    ParameterStatus status = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    return status == ParameterStatus::NORMAL;
}


bool checkSoc(float soc) {
    ParameterStatus status = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    return status == ParameterStatus::NORMAL;
}


bool checkChargeRate(float chargeRate) {
    ParameterStatus status = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);
    return status == ParameterStatus::NORMAL;
}


bool batteryIsOk(float temperature, float soc, float chargeRate) {

    ParameterStatus tempStatus = getParameterStatus(temperature, TEMPERATURE_BREACH_RANGE, TEMPERATURE_WARNING_RANGE);
    ParameterStatus socStatus = getParameterStatus(soc, SOC_BREACH_RANGE, SOC_WARNING_RANGE);
    ParameterStatus chargeRateStatus = getParameterStatus(chargeRate, CHARGE_RATE_BREACH_RANGE, CHARGE_RATE_WARNING_RANGE);

    std::cout << statusToMessageTranslation("Temperature", tempStatus) << std::endl;
    std::cout << statusToMessageTranslation("State of Charge", socStatus) << std::endl;
    std::cout << statusToMessageTranslation("Charge Rate", chargeRateStatus) << std::endl;


    bool tempOk = tempStatus == ParameterStatus::NORMAL;
    bool socOk = socStatus == ParameterStatus::NORMAL;
    bool chargeRateOk = chargeRateStatus == ParameterStatus::NORMAL;


    return tempOk && socOk && chargeRateOk;
}
