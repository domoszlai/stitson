#include "ps2input.h"

PS2Input::PS2Input(int pinDAT, int pinCMD, int pinSEL, int pinCLK, Command* command)
{
    this->command = command;  
    
    // SKIP error...
    ps2x.config_gamepad(pinCLK, pinCMD, pinSEL, pinDAT, false, false);
}

bool PS2Input::loop()
{
    ps2x.read_gamepad(false, false);

    if(ps2x.ButtonPressed(PSB_CIRCLE))
    {
      command->play(SIREN, 1);
    }
    
    if(ps2x.ButtonPressed(PSB_CROSS))
    {
      command->play(MELODY1, 1);
    }    

    if(ps2x.ButtonPressed(PSB_L1))
    {
      command->lightOn();
    }    

    if(ps2x.ButtonPressed(PSB_L2))
    {
      command->lightOff();
    }    

    if(ps2x.ButtonPressed(PSB_R1))
    {
      command->play(SIREN, -1);
      command->lightOn();
    }    

    if(ps2x.ButtonPressed(PSB_R2))
    {
      command->mute();
      command->lightOff();
    }    

    byte y = ps2x.Analog(PSS_LY);
    if(y > 128)
    {
        command->goForward();
    }
    else if(y < 128)
    {
        command->goBackward();
    }
    else
    {
        command->stop();        
    }
    
    sleep_milli(50);
    
    return true;
}

