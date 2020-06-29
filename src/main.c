#include <at89x52.h>
#include "../inc/frog.h"

u8 delaycount = 0;
u8 pitch_pos = 0;

u8 code pitch_TH[] = {
    0xF8, 0xF8, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE};

u8 code pitch_TL[] = {
    0x88, 0xF4, 0x59, 0xB8, 0x13, 0x68, 0xB8, 0x04, 0x4C, 0x8F, 0xCF, 0x0B,
    0x44, 0x7A, 0xAC, 0xDC, 0x09, 0x34, 0x5C, 0x82, 0xA6, 0xC7, 0xE7, 0x05};

void main(void)
{
    TMOD = 0x11; // Timer 0, 1 are 16 bit mode
    ET0 = ET1 = 1; // Enable timers' interrupt
    EX0 = 1; // Enable external interrupt
    IT0 = 1; // Set interrupt mode to falling edge
    EA = 1; // Enable main interrupt flag

    for (;;)
        ;
}

void onBtnPress(void) interrupt 0
{
    EX0 = 0;

    TH1 = (65536 - 50000) / 256;
    TL1 = (65536 - 50000) % 256;
    TR1 = 1;

    TH0 = pitch_TH[pitch_pos];
    TL0 = pitch_TL[pitch_pos];
    TR0 = 1;
}

void onTimer0(void) interrupt 1 // Speaker oscillator
{
    TH0 = pitch_TH[pitch_pos];
    TL0 = pitch_TL[pitch_pos];
    SP = !SP;
}

void onTimer1(void) interrupt 3 // Speaker note timer
{
    if (delaycount > 2)
    {
        TR0 = TR1 = 0;
        if (pitch_pos < 19)
            pitch_pos++;
        else
            pitch_pos = 0;
        delaycount = 0;
        EX0 = 1;
    }
    else
    {
        TH1 = (65536 - 50000) / 256;
        TL1 = (65536 - 50000) % 256;
        delaycount++;
        TR1 = 1;
    }
}
