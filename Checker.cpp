#include <cassert>
#include <iostream>
#include <string>

// Enumeration to represent the status of each parameter
enum ParameterStatus {
    LOW_BREACH,
    LOW_WARNING,
    NORMAL,
    HIGH_WARNING,
    HIGH_BREACH
};

// Structure to hold the boundary values for each condition
struct ParameterRange {
    float lowBreach;
    float lowWarning;
    float highWarning;
    float highBreach;
};

// Function to determine if the value is in breach
ParameterStatus getBreachStatus(float value, const ParameterRange& range) {
    if (value < range.lowBreach) {
        return LOW_BREACH;
    }
    if (value >= range.highBreach) {
        return HIGH_BREACH;
    }
    return NORMAL; // Not in breach
}

// Function to determine the warning status
ParameterStatus getWarningStatus(float value, const ParameterRange& range) {
    if (value < range.lowWarning) {
        return LOW_WARNING;
    }
    if (value >= range.highWarning) {
        return HIGH_WARNING;
    }
    return NORMAL; // Normal if not in any warning range
}

// Function to determine the status of a parameter given its range
ParameterStatus getParameterStatus(float value, const ParameterRange& range) {
    ParameterStatus breachStatus = getBreachStatus(value, range);
    if (breachStatus != NORMAL) {
        return breachStatus;  // Return if it's a breach
    }
    return getWarningStatus(value, range); // Check warning status if not a breach
}

// Function to translate the parameter status to a human-readable message
std::string translateStatusToMessage(const std::string& parameter, ParameterStatus status) {
    static const std::string messages[] = {
        parameter + " is below the safe range!",   // LOW_BREACH
        "Warning: " + parameter + " is approaching discharge.", // LOW_WARNING
        parameter + " is normal.",                // NORMAL
        "Warning: " + parameter + " is approaching charge-peak.", // HIGH_WARNING
        parameter + " is above the safe range!"   // HIGH_BREACH
    };

    if (status < LOW_BREACH || status > HIGH_BREACH) {
        return "Unknown status for " + parameter;
    }

    return messages[status];
}

// Function to check the temperature status and print appropriate messages
bool checkTemperature(float temperature) {
    ParameterRange temperatureRange = {0, 0 + 45 * 0.05, 45 - 45 * 0.05, 45};
    ParameterStatus status = getParameterStatus(temperature, temperatureRange);
    std::cout << translateStatusToMessage("Temperature", status) << std::endl;
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to check the State of Charge (SoC) status and print appropriate messages
bool checkSoc(float soc) {
    ParameterRange socRange = {20, 20 + 80 * 0.05, 80 - 80 * 0.05, 80};
    ParameterStatus status = getParameterStatus(soc, socRange);
    std::cout << translateStatusToMessage("State of Charge", status) << std::endl;
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to check the charge rate status and print appropriate messages
bool checkChargeRate(float chargeRate) {
    ParameterRange chargeRateRange = {0, 0, 0.8 - 0.8 * 0.05, 0.8};
    ParameterStatus status = getParameterStatus(chargeRate, chargeRateRange);
    std::cout << translateStatusToMessage("Charge Rate", status) << std::endl;
    return status != LOW_BREACH && status != HIGH_BREACH;
}

// Function to evaluate the overall battery status
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    bool tempOk = checkTemperature(temperature);
    bool socOk = checkSoc(soc);
    bool chargeRateOk = checkChargeRate(chargeRate);
    return tempOk && socOk && chargeRateOk;
}

int main() {
    // Test cases to verify battery safety checks and warning messages
    assert(batteryIsOk(25, 70, 0.7) == true);  // Within normal range
    assert(batteryIsOk(50, 85, 0) == false);   // Temperature and SoC out of range
    assert(batteryIsOk(-1, 50, 0.5) == false); // Temperature out of range
    assert(batteryIsOk(25, 10, 0.5) == false); // SoC out of range
    assert(batteryIsOk(25, 50, 0.9) == false); // Charge rate out of range
    assert(batteryIsOk(42, 78, 0.6) == true);  // Within warning range
    assert(batteryIsOk(1, 21, 0.76) == true);  // Within warning range

    std::cout << "All tests passed!\n";
    return 0;
}
