#include <AT89X52.H>
#include "../inc/frog.h"

void sp_init()
{
    TMOD = 0x11; // Timer 0, 1 are 16 bit mode
    ET0 = ET1 = 1; // Enable timers' interrupt
    EX0 = 1; // Enable external interrupt
    IT0 = 1; // Set interrupt mode to falling edge
    EA = 1; // Enable main interrupt flag
}

void sp_play(u8 sound)
{

}
