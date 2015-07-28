#include "command.h"

Command::Command(Wheel* FL, Wheel* FR, Wheel* RL, Wheel* RR, Speaker* speaker)
{
    this->FL = FL;
    this->FR = FR;
    this->RL = RL;
    this->RR = RR;
    this->speaker = speaker;
        
    this->speed = 1;
    this->maxMovement = 30;
    this->endTime = 0; // turn off timer
}

void Command::play(Melody melody, int count)
{
    speaker->play(melody, count);  
}

void Command::setSpeed(float speed)
{
    this->speed = speed;

    FL->setSpeed(speed);  
    FR->setSpeed(speed);    
    RL->setSpeed(speed);  
    RR->setSpeed(speed);    
}

float Command::getSpeed()
{
    return this->speed;  
}

void Command::setMaxMovementTime(int millis)
{
    this->maxMovement = millis; 
}

void Command::startTimer()
{
  this->endTime = millis() + this->maxMovement;
}

void Command::goForward()
{
    FL->goForward();
    FR->goForward();    
    RL->goForward();
    RR->goForward();
    this->startTimer();
}

void Command::goBackward()
{
    FL->goBackward();
    FR->goBackward();    
    RL->goBackward();
    RR->goBackward();    
    this->startTimer();    
}

void Command::stop()
{
    FL->stop();
    FR->stop();    
    RL->stop();
    RR->stop();
    this->endTime = 0; // turn off timer                
}

void Command::turnLeft()
{
    FL->stop();
    FR->goForward();    
    RL->stop();
    RR->goForward();
    this->startTimer();    
}

void Command::turnRight()
{
    FR->stop();
    FL->goForward();    
    RL->goForward();
    RR->stop();    
    this->startTimer();  
}

bool Command::loop()
{
    if(this->endTime > 0)
    {
        if(millis() > this->endTime)
        {
            this->stop();
        }  
    }
    
    return true;    
}

