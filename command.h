#ifndef COMMAND_H
#define COMMAND_H

#define MINDISTANCE 6

#include "mthread.h"
#include "wheel.h"
#include "speaker.h"
#include "hcsr04.h"
#include "light.h"

class Command : public Thread
{
public:
    Command(Wheel* FL, Wheel* FR, Wheel* RL, Wheel* RR, Speaker* speaker, HCSR04* D, Light* light);

    void setSpeed(float speed); // 0-1
    float getSpeed();
    
    void setMaxMovementTime(int millis);

    void goForward();
    void goBackward();
    void stop();
    void turnLeft();
    void turnRight();
    
    void play(Melody melody, int count); // -1 means until stop    
    void mute();
    
    void lightOn();
    void lightOff();
    
protected:
    bool loop();
    
private:
    void startTimer();

    float speed;
    int maxMovement;     
    long endTime;
    bool forward; 
    
    Wheel* FL;
    Wheel* FR;
    Wheel* RL;
    Wheel* RR;
    Speaker* speaker;
    HCSR04* D;
    Light* light;
};

#endif  // COMMAND_H
