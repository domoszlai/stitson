#ifndef WHEEL_H
#define WHEEL_H

#include <mthread.h>

class Wheel : public Thread
{
public:
    Wheel(int speedPin, int dir1Pin, int dir2Pin);
    void goForward();
    void goBackward();
    void stop();
    
    void setSpeed(float speed); // 0-1
    float getSpeed();
protected:
    bool loop();
private:
    enum State
    {
        FORWARD,
        BACKWARD,
        STOP
    };

    void changeDir(bool dir1, bool dir2);

    float speed;
    int speedPin;
    int dir1Pin;
    int dir2Pin;
    State state;
};

#endif  // WHEEL_H
