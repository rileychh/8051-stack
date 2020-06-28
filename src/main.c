#include <AT89X52.H>
#define SP P3_4

void setup();
unsigned char delaycount = 0;
unsigned char pitch_pos = 0;

code unsigned char pitch_TH[] =
	{
		0xF8, 0xF8, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
		0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE};

code unsigned char pitch_TL[] =
	{
		0x88, 0xF4, 0x59, 0xB8, 0x13, 0x68, 0xB8, 0x04, 0x4C, 0x8F, 0xCF, 0x0B,
		0x44, 0x7A, 0xAC, 0xDC, 0x09, 0x34, 0x5C, 0x82, 0xA6, 0xC7, 0xE7, 0x05};
void setup(void)
{
	TMOD = 0x11;
	ET0 = 1;
	ET1 = 1;
	EX0 = 1;
	IT0 = 1;
	EA = 1;
}

void main(void)
{
	setup();
	for (;;)
		;
}

void btnPress(void) interrupt 0
{
	EX0 = 0;

	TH1 = (65536 - 50000) / 256;
	TL1 = (65536 - 50000) % 256;
	TR1 = 1;

	TH0 = pitch_TH[pitch_pos];
	TL0 = pitch_TL[pitch_pos];
	TR0 = 1;
}

void pitchPlay(void) interrupt 1
{
	TH0 = pitch_TH[pitch_pos];
	TL0 = pitch_TL[pitch_pos];
	SP = !SP;
}

void pitchDelay(void) interrupt 3
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
