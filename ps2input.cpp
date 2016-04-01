
#include "ps2input.h"
#include "robotcar.h"

PS2Input::PS2Input(int pinDAT, int pinCMD, int pinSEL, int pinCLK, Command* command)
{
    this->command = command;  
    
    // SKIP error...
    ps2x.config_gamepad(pinCLK, pinCMD, pinSEL, pinDAT, false, false);
}

bool PS2Input::loop()
{ 
    if(!ps2x.read_gamepad(false, 0x00)) return true;

    if(ps2x.ButtonPressed(PSB_CIRCLE))
    {
      #ifdef DEBUG 
      Serial.println("circle");
      #endif
      
      command->play(SIREN, 1);
    }
        
    if(ps2x.ButtonPressed(PSB_CROSS))
    {
      #ifdef DEBUG       
      Serial.println("cross");
      #endif
      
      command->play(MELODY1, 1);
    }    

    if(ps2x.ButtonPressed(PSB_L1))
    {
      #ifdef DEBUG       
      Serial.println("L1");      
      #endif
      
      command->lightOn();
    }    

    if(ps2x.ButtonPressed(PSB_L2))
    {
      #ifdef DEBUG 
      Serial.println("L2");      
      #endif
      
      command->lightOff();
    }    

    if(ps2x.ButtonPressed(PSB_R1))
    {
      #ifdef DEBUG 
      Serial.println("R1");      
      #endif
      
      command->play(SIREN, -1);
    }    

    if(ps2x.ButtonPressed(PSB_R2))
    {
      #ifdef DEBUG 
      Serial.println("R2");      
      #endif
      
      command->mute();
    }    

    byte y = ps2x.Analog(PSS_LY);
    if(y > 128)
    {
        #ifdef DEBUG
        Serial.print("BACKWARD: ");
        Serial.println(y);
        #endif
        
        command->setSpeed((y-129)/129.0);
        command->goBackward();
    }
    else if(y < 126)
    {
        #ifdef DEBUG      
        Serial.print("FORWARD: ");
        Serial.print(y);
        Serial.print(", SPEED: ");
        Serial.println((127-y)/127.0);
        #endif
        
        command->setSpeed((127-y)/127.0);
        command->goForward();
    }
    else
    {
        byte x = ps2x.Analog(PSS_LX);
        if(x > 160) // My device is slightly broken...
        {
            #ifdef DEBUG     
            Serial.print("RIGHT: ");      
            Serial.println(x);                  
            #endif
            
            command->setSpeed(1);
            command->turnRight();
        }
        else if(x < 120)
        {
            #ifdef DEBUG 
            Serial.print("LEFT: ");             
            Serial.println(x);
            #endif
            
            command->setSpeed(1);
            command->turnLeft();
        }
        else
        {
          command->stop();
        }
    }
    
    sleep_milli(20);
    
    return true;
}

