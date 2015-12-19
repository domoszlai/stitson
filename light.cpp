#include "light.h"

Light::Light(int pin)
{
    this->pin = pin;
    pinMode(pin,OUTPUT);       
}

void Light::start()
{
    digitalWrite(pin, HIGH);
}

void Light::stop()
{
    digitalWrite(pin, LOW);
}

bool Light::loop()
{
    return false;
}

