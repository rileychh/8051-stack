#include <AT89X52.H>
#include "../inc/frog.h"
#include "sp.c"

u8 dotm_buf[8];

// GAMESTATS
u8 isOver = 0;
u8 score = 0;
u8 stackHeight = 0;
u8 currStack = 0;

void main()
{
    sp_init();

    while (!isOver)
    {

        dotm_put(dotm_buf);
    }
}

code u8 pitch_TH[] = {
    0xF8, 0xF8, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0xF1, 0xEE};

code u8 pitch_TL[] = {
    0x88, 0xF4, 0x59, 0xB8, 0x13, 0x68, 0xB8, 0x04, 0x4C, 0x8F, 0xCF, 0x0B, 0x44,
    0x7A, 0xAC, 0xDC, 0x09, 0x34, 0x5C, 0x82, 0xA6, 0xC7, 0xE7, 0x05, 0x11, 0x3E};

void onBtnPress() interrupt 0
{
    EX0 = 0;

    TH1 = TH_50MS;
    TL1 = TL_50MS;
    TR1 = 1;

    TH0 = pitch_TH[pitch_pos];
    TL0 = pitch_TL[pitch_pos];
    TR0 = 1;
}

void onTimer0() interrupt 1 // Speaker oscillator.  //0 means you loss one but didn't lose, 1 means you get the point perfectly, 2 means you lose
{
    TH0 = pitch_TH[sp_play(1)];
    TL0 = pitch_TL[sp_play(1)];
    SP = !SP;
}

void onTimer1() interrupt 3 // Speaker note timer
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
        TH1 = TH_50MS;
        TL1 = TL_50MS;
        delaycount++;
        TR1 = 1;
    }
}

void scan_delay(u8 time)
{
    u8 i;

    while (time)
    {
        for (i = 120; i; i--);
        time--;
    }
}
