#ifndef SERIALINPUT_H
#define SERIALINPUT_H

#include <QueueList.h>
#include <mthread.h>
#include "command.h"

#define MOVEMENT_TIME 500
//#define REALTIME

class SerialInput : public Thread
{
public:
    SerialInput(Command* command);    
protected:
    bool loop();
private:
    QueueList<int>* queue;
    Command* command;
    long lastCommandTime;
};

#endif  // SERIALINPUT_H
