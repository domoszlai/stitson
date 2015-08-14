#include "serialinput.h"

SerialInput::SerialInput(Command* command)
{
    this->command = command;
    this->queue = new QueueList<int>();
    this->lastCommandTime = 0;
    
    command->setMaxMovementTime(MOVEMENT_TIME);
}

bool SerialInput::loop()
{
    if (Serial.available() > 0) 
    {
        int inByte = Serial.read();
        queue->push(inByte);
    }
    
    // Check timer
    if(lastCommandTime > 0 && lastCommandTime + MOVEMENT_TIME < millis()) lastCommandTime = 0;
      
    if (lastCommandTime == 0 && !queue->isEmpty())
    {

        int cmd = queue->pop();
        bool movement = true;
        
        switch (cmd) {
        case 'w':
            command->goForward();        
            break;
        case 's':
            command->goBackward();        
            break;
        case 'a':
            command->turnLeft();        
            break;
        case 'd':
            command->turnRight();        
            break;
        case '1':
            command->play(SIREN, 1);
            movement = false;
            break;
        case '2':
            command->play(MELODY1, 1);
            movement = false;            
            break;
        case '[':
            command->lightOn();
            movement = false;            
            break;            
        case ']':
            command->lightOff();
            movement = false;            
            break;            
        }   
        
#ifndef REALTIME
        if(movement) lastCommandTime = millis();
#endif
        
    }  
    return true;
}

