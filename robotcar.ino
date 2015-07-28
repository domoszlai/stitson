#include "mthread.h"
#include "wheel.h"
#include "command.h"
#include "speaker.h"
#include "serialinput.h"

Wheel RR(5, 3, 4);
Wheel FR(6, 7, 8);
Wheel FL(9, 11, 12);
Wheel RL(10, 13, 2);

Speaker speaker(A0);

Command command(&FL,&FR,&RL,&RR,&speaker);

void setup()
{
    // Initialize the serial connection:
    Serial.begin(9600);
    
    main_thread_list->add_thread(&FL);  
    main_thread_list->add_thread(&FR);  
    main_thread_list->add_thread(&RL);
    main_thread_list->add_thread(&RR);  
    main_thread_list->add_thread(&speaker);
    main_thread_list->add_thread(&command); 
    
    main_thread_list->add_thread(new SerialInput(&command));    
    
//    command.setMaxMovementTime(500);
//    command.turnLeft();
//    command.play(MELODY1, 2);
  
    //BL.goForward();
    //delay(500);
    //BL.setSpeed(0.2);    
}


