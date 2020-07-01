#include <AT89X52.H>
#include "../inc/frog.h"

u8 dotm_buf[8];

// GAMESTATS
code u8 TICK_SPEED = 12; // Unit: 4ms
u8 score = 0;
u8 combo = 0;
u8 stackHeight = 0;
u8 currLine = 0;
i8 linePos = 0; // L/R movement
u8 moveLeft = 1; // 0: move to right every tick; 1: move to left
u8 gameOver = 0;


void main()
{
    u8 i, j;

    sp_init();

    // dotm init
    for (i = 0; i < 8; i++) dotm_buf[i] = 0x0;
    dotm_buf[7 - i] = 0x7e; // button: 00****00
    
    while (!gameOver)
    {
        if (moveLeft)
        {
            dotm_buf[linePos] << 1;
            linePos--;
        } 
        else
        {
            dotm_buf[linePos] >> 1;
            linePos++;
        }

        if (linePos == -6 || linePos == 6) 
        {
            moveLeft = !moveLeft;
        }
        
        ssd_put(score);
        dotm_put(dotm_buf);
        for (i = 0; i < TICK_SPEED; i++)
            for (j = 480; j; j--);
    }

    sp_play(8);
    for (;;)
    {
        ssd_put(score);
        dotm_put(dotm_buf);
    }
}

void onBtnPress() interrupt 0
{
    u8 i;

    for (i = 0; i < 8; i++)
    {
        // If a LED is on but the below one isn't
        if (dotm_buf[7 - linePos] >> i & 1
          > dotm_buf[6 - linePos] >> i & 1)
        {
            dotm_buf[linePos] &= ~(1 << i); // that LED is cleared
        }
    }

    // If all LEDs are cleared
    if (!dotm_buf[7 - linePos]) 
    {
        gameOver = 1;
        return;
    }

    sp_play(combo);
    combo++;
    if (combo == 7)
    {
        combo = 0;
        sp_play(7);
    }
}

code u8 pitch_TH[] = {
    0xf8, 0xfc, 0xf9, 0xfc, 0xfa, 0xfd, 0xfa, 0xfd, 0xfb,
    0xfd, 0xfb, 0xfd, 0xfc, 0xfe, 0xfe, 0xff, 0xE2, 0xC4};
code u8 pitch_TL[] = {
    0x88, 0x44, 0x59, 0xac, 0x13, 0x09, 0x68, 0x34, 0x04,
    0x82, 0x8f, 0xc7, 0x0b, 0x05, 0x22, 0x11, 0x23, 0x46};

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

void scan_delay(u8 time)
{
    u8 i;

    while (time)
    {
        for (i = 120; i; i--);
        time--;
    }
}
