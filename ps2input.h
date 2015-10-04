#ifndef PS2INPUT_H
#define PS2INPUT_H

#include "PS2X_lib.h"
#include "mthread.h"
#include "command.h"

class PS2Input : public Thread
{
public:
    PS2Input(int pinDAT, int pinCMD, int pinSEL, int pinCLK, Command* command);    
protected:
    bool loop();
private:
    Command* command;
    PS2X ps2x;
};

#endif  // PS2INPUT_H
