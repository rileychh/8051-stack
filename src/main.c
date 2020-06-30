#include <AT89X52.H>
#include "../inc/frog.h" 

u8 delaycount = 0;
u8 pitch_pos = 0;

u8 dotm_buf[8];

// GAMESTATS
u8 isOver = 0;
u8 score = 0;
u8 stackHeight = 0;
u8 currStack = 0;

void main(void)
{
    sp_init();

    for (;;)
    {
        dotm_put(dotm_buf);
    }
}

code u8 pitch_TH[] = {
    0xF8, 0xF8, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE};

code u8 pitch_TL[] = {
    0x88, 0xF4, 0x59, 0xB8, 0x13, 0x68, 0xB8, 0x04, 0x4C, 0x8F, 0xCF, 0x0B,
    0x44, 0x7A, 0xAC, 0xDC, 0x09, 0x34, 0x5C, 0x82, 0xA6, 0xC7, 0xE7, 0x05};

void delay ()
{

}
		
void onBtnPress() interrupt 0
{
    EX0 = 0;

    TH1 = (65536 - 50000) / 256;
    TL1 = (65536 - 50000) % 256;
    TR1 = 1;

    TH0 = pitch_TH[pitch_pos];
    TL0 = pitch_TL[pitch_pos];
    TR0 = 1;
	
		MoveBool = 0 ;
}

void onTimer0() interrupt 1 // Speaker oscillator
{
    TH0 = pitch_TH[pitch_pos];
    TL0 = pitch_TL[pitch_pos]; 
    SP = !SP;
}

void onTimer1() interrupt 3 // Speaker note timer
{
    if (delaycount > 2)
    {
        TR0 = TR1 = 0;
			
        if     (pitch_pos < 19)  pitch_pos++;
        else    pitch_pos = 0;
			
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

void scan (void)
{
	int i ;
	for (i=0 ; i<=8 ; i++)
	{
		dotm_put( LEDdot[i][] );
	}
	
}

void main (void)
{
	int i ;
	
	while(1)
	{
		
		
		
	}
}
