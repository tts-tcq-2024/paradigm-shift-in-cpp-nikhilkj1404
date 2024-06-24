#include <assert.h>
#include <iostream>
using namespace std;

struct RangeCheck {
  float value;
  float min;
  float max;
  const char* parameterName;
};

struct RangeCheckResult {
  bool isOk;
  const char* parameterName;
  const char* breachType;
};

bool isValueInRange (float value, float min, float max) {
  return value >= min && value <= max;
}

RangeCheckResult checkRange(const RangeCheck* checks, size_t numChecks) {
  for (size_t i =0; i < numChecks; ++i) {
    if (!isValueInRange(check[i].value, checks[i].min, checks[i].max)) {
      const char* breachType = (checks[i].value < checks[i].min) ? "low" : "high";
      return { false, checks[i].parameterName, breachType };
    }
  }
  return { true, nullptr, nullptr };
}

bool batteryIsOk(float temperature, float soc, float chargeRate, RangeCheckResult* result) {
  RangeCheck checks[] = {
  {temperature, 0, 45, "Temperature"},
  {soc, 20, 80, "State of Charge"},
  {chargeRate, 0, 0.8, "Charge Rate"}
};

*result = checkRange(checks, sizeof(checks) / sizeof(checks[0]));
return result->isOk;
}

void checkAndPrintBatteryStatus(float temperature, float soc, float chargeRate) {
  RangeCheckResult result;
  if (!batteryIsOk(temperature, soc, chargeRate, &result)) {
    cout << result.parameterName << " out of range (" << result.breachType << ")\n";
  } else {
    cout << "Battery parameters are OK\n";
  }
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
