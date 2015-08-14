#include "light.h"

Light::Light(int RPin, int GPin, int BPin)
{
    this->RPin = RPin;
    this->GPin = GPin;
    this->BPin = BPin;

    this->state = -1;
    
    pinMode(RPin,OUTPUT);
    pinMode(GPin,OUTPUT);
    pinMode(BPin,OUTPUT);
}

void Light::set(float r, float g, float b)
{
    analogWrite(RPin, r*255);
    analogWrite(GPin, g*255);  
    analogWrite(BPin, b*255);
}

void Light::start()
{
    this->state = 0;
}

void Light::stop()
{
    set(0,0,0);
    this->state = -1;
}

bool Light::loop()
{
    if(this->state == 0)
    {
	set(1,0,0);
        state++;
        sleep_milli(100);         
    }
    else if(this->state == 1)
    {
	set(1,0,1);
        state++;
        sleep_milli(100);               
    }
    else if(this->state == 2)
    {
	set(0,0,1);
        state = 0;
        sleep_milli(100);               
    }
    
    return true;
}

