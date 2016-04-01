#include "acs712.h"

ACS712::ACS712(int pin)
{
    this->pin = pin;
    pinMode(pin,INPUT);       
}

bool ACS712::loop()
{
    int rawValue = analogRead(pin);
    double voltage = (rawValue / 1023.0) * 5000; 
    double amps = ((voltage - 2500) / MVPERAMP);

    Serial.println(amps);

    sleep_milli(5);
  
    return true;
}

