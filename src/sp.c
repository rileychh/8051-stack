#include <AT89X52.H>
#include "../inc/frog.h"

void sp_init()
{
  TMOD = 0x11;   // Timer 0, 1 are 16 bit mode
  ET0 = ET1 = 1; // Enable timers' interrupt
  EX0 = 1;       // Enable external interrupt
  IT0 = 1;       // Set interrupt mode to falling edge
  EA = 1;        // Enable main interrupt flag
}

unsigned char sp_play(u8 sound) //0 means you loss one but didn't lose, 1 means you get the point perfectly, 2 means you lose
{
  if (sound == 0)
  {
    pitch_pos = 24;
  }
  else if (sound == 1)
  {
    pitch_pos++;
  }
  else
  {
    pitch_pos = 25;
  }
  return pitch_pos;
}
