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

code u8 _pitch_TH[] = {
    0xf8, 0xfc, 0xf9, 0xfc, 0xfa, 0xfd, 0xfa, 0xfd,
    0xfb, 0xfd, 0xfb, 0xfd, 0xfc, 0xfe, 0xfe, 0xff};
code u8 _pitch_TL[] = {
    0x88, 0x44, 0x59, 0xac, 0x13, 0x09, 0x68, 0x34,
    0x04, 0x82, 0x8f, 0xc7, 0x0b, 0x05, 0x22, 0x11};

void sp_play(u8 sound)
{
    currNote = 0;
    pitch_pos = sound; // TODO dummy

    TH1 = TH_50MS;
    TL1 = TL_50MS;
    TR1 = 1;

    TH0 = currNote == 0 ? _pitch_TH[pitch_pos] : _pitch_TH[pitch_pos + 1];
    TL0 = currNote == 0 ? _pitch_TL[pitch_pos] : _pitch_TL[pitch_pos + 1];
    TR0 = 1;

    while (currNote < 2); // Wait for 2 notes to play
    currNote = 0;
    //pitch_pos = pitch_pos == 14 ? pitch_pos = 0 : pitch_pos = pitch_pos + 2;
}
