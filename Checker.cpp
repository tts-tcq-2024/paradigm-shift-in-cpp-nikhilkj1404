#include <assert.h>
#include <iostream>
using namespace std;

void printErrorMessage(const char* parameter) {
 cout << parameter << "out of range!\n";
}
 
bool isTemperatureOk(float temperature) {
  if(temperature < 0 || temperature > 45) {
    printErrorMessage("Temperature");
    return false;
  }
  return true;
}
 
bool isSocOk(float soc) {
  if(soc < 20 || soc > 80) {
    printErrorMessage("State of Charge");
    return false;
  }
  return true;
}
 
bool isChargeRateOk(float chargeRate) {
  if(chargeRate > 0.8) {
    printErrorMessage("Charge Rate");
    return false;
  }
  return true;
}
 
bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}
 
int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
