#include <AT89X52.H>
#include "../../inc/frog.h"

void sp_init();
void sp_play(u8 sound);

code u8 pitch_TH[] = {
    0xf8, 0xfc, 0xf9, 0xfc, 0xfa, 0xfd, 0xfa, 0xfd, 0xfb,
    0xfd, 0xfb, 0xfd, 0xfc, 0xfe, 0xfe, 0xff, 0xE2, 0xC4};
code u8 pitch_TL[] = {
    0x88, 0x44, 0x59, 0xac, 0x13, 0x09, 0x68, 0x34, 0x04,
    0x82, 0x8f, 0xc7, 0x0b, 0x05, 0x22, 0x11, 0x23, 0x46};

u8 currNote = 0, pitch_pos = 0;
u8 pos = 0, i;
int time;

void main()
{
    sp_init();

    for (;;)
    {
        if (pos > 16)
            pos = 0;

        time = 1000;

        while (time)
        {
            for (i = 120; i; i--)
                ;
            time--;
        }
    }
}

void sp_init()
{
    TMOD = 0x11;   // Timer 0, 1 are 16 bit mode
    ET0 = ET1 = 1; // Enable timers' interrupt
    EX0 = 1;       // Enable external interrupt
    IT0 = 1;       // Set interrupt mode to falling edge
    EA = 1;        // Enable main interrupt flag
}

void btnPress() interrupt 0
{
    sp_play(pos);
    pos++;
}

void onTimer0() interrupt 1 // Speaker oscillator
{
    TR0 = 0;
    TH0 = currNote == 0 ? pitch_TH[pitch_pos] : pitch_TH[pitch_pos + 1];
    TL0 = currNote == 0 ? pitch_TL[pitch_pos] : pitch_TL[pitch_pos + 1];
    SP = !SP;
    TR0 = 1;
}

void onTimer1() interrupt 3 // Speaker note timer
{
    TR1 = TR0 = 0; // SP OFF
    TH1 = TH_50MS;
    TL1 = TL_50MS;
    currNote++;
    TR1 = 1;
}

void sp_play(u8 sound)
{
    currNote = 0;
    pitch_pos = sound; // TODO dummy

    TH1 = TH_50MS;
    TL1 = TL_50MS;
    TR1 = 1;

    TH0 = currNote == 0 ? pitch_TH[pitch_pos] : pitch_TH[pitch_pos + 1];
    TL0 = currNote == 0 ? pitch_TL[pitch_pos] : pitch_TL[pitch_pos + 1];
    TR0 = 1;

    while (currNote < 2)
        ; // Wait for 2 notes to play
    currNote = 0;
    //pitch_pos = pitch_pos == 14 ? pitch_pos = 0 : pitch_pos = pitch_pos + 2;
}
