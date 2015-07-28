#include "mthread.h"
#include "wheel.h"

Wheel::Wheel(int speedPin, int dir1Pin, int dir2Pin)
{
    this->speedPin = speedPin;
    this->dir1Pin = dir1Pin;    
    this->dir2Pin = dir2Pin;
    this->speed = 1;   
    this->state = STOP;   
    
    pinMode(dir1Pin,OUTPUT);  
    pinMode(dir2Pin,OUTPUT);  
    pinMode(speedPin,OUTPUT);
}

void Wheel::changeDir(bool dir1, bool dir2)
{
    analogWrite(this->speedPin, this->speed*255); //Sets speed variable via PWM 
    digitalWrite(this->dir1Pin, dir1);
    digitalWrite(this->dir2Pin, dir2);        
}

void Wheel::goForward()
{
    this->state = FORWARD;
    changeDir(LOW, HIGH);
}

void Wheel::goBackward()
{
    this->state = BACKWARD;
    changeDir(HIGH, LOW);
}

void Wheel::stop()
{
    this->state = STOP;
    changeDir(LOW, LOW);
}

void Wheel::setSpeed(float speed)
{
    if(speed < 0 || speed > 1) return;
    this->speed = speed;
    
    // Set new speed if the motor is working
    if(state == FORWARD)
    {
        goForward();
    }
    else if(state == BACKWARD)
    {
        goBackward();  
    }
}

float Wheel::getSpeed()
{
    return this->speed;  
}

bool Wheel::loop()
{
}

