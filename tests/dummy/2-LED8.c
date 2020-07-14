#include <AT89X52.H>
#define SP P3_4
#define u8 unsigned char
#define TH_50MS 60
#define TL_50MS 176

void setup(void);
void sp_play(u8 sound);
void delayms(int time);
void Light();
void move(int num);
int key_button(void);
void key_search(void);
void btnPress(void);

unsigned char delaycount = 0;
unsigned char pitch_pos, sound = 0;

code unsigned char pitch_TH[] =
	{
		0xF8, 0xF8, 0xF9, 0xF9, 0xFA, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC,
		0xFC, 0xFC, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE};

code unsigned char pitch_TL[] =
	{
		0x88, 0xF4, 0x59, 0xB8, 0x13, 0x68, 0xB8, 0x04, 0x4C, 0x8F, 0xCF, 0x0B,
		0x44, 0x7A, 0xAC, 0xDC, 0x09, 0x34, 0x5C, 0x82, 0xA6, 0xC7, 0xE7, 0x05};

//code unsigned char music[]={1,0xff,0xff,2,3,0xff,4,5,0xff};
code unsigned char table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
unsigned char input[8] = {0xff};
code unsigned char com[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
code unsigned char but_com[] = {0x7f, 0xbf, 0xdf, 0xef}; //;{0xef,0xdf,0xbf,0x7f};

int deJump;
int Key;
int howlong = 8;

void setup(void)
{
	TMOD = 0x11;   // Timer 0, 1 are 16 bit mode
	ET0 = ET1 = 1; // Enable timers' interrupt
	EX0 = 1;	   // Enable external interrupt
	IT0 = 1;	   // Set interrupt mode to falling edge
	EA = 1;		   // Enable main interrupt flag
	IT0 = 1;
	PX0 = 1;
}

void main(void)
{
	unsigned char i = 0;
	setup();

	for (;;)
	{
		if (!P3_2)
		{
			delayms(30);
			if (!P3_2)
			{
				if (input[i] != 0xff)
				{
					for (i = 0; i < 8; i++)
					{
						sp_play(input[i]);
						delayms(500);
					}
				}
			}
		}
		key_search();
		Light();
	}
}

void Light()
{
	unsigned char i;
	for (i = 0; i <= 7; i++)
	{
		P2 = 0x00;
		P1 = com[i];
		P2 = table[input[i + (howlong - 8)]];
		delayms(2);
	}
}

void move(int num)
{
	int j;

	for (j = 0; j < howlong; j = j + 1)
	{
		input[j] = input[j + 1];
	}

	input[howlong - 1] = num;
}

int key_button(void)
{

	unsigned int ScanCode = 0;
	for (ScanCode = 0; ScanCode < 4; ScanCode = ScanCode + 1)
	{

		P0 = but_com[ScanCode];

		if (P0_0 == 0)
			return (4 * (ScanCode) + 0);

		if (P0_1 == 0)
			return (4 * (ScanCode) + 1);

		if (P0_2 == 0)
			return (4 * (ScanCode) + 2);

		if (P0_3 == 0)
			return (4 * (ScanCode) + 3);
	}
	return -1;
}

void key_search(void)
{

	Key = key_button();

	if (Key == -1)
	{

		deJump = 1;
	}
	else if (deJump)
	{
		move(Key);
		deJump = 0;
	}
}

//void btnPress(void)
//{
//	int i ;
//	for(i = 0;i<8;i++)
//		{
//			if(music[i] != 0xff )
//			{
//				sp_play(music[i]);
//				delayms(1000);
//			}
//
//		}
//}

void onTimer0() interrupt 1 // Speaker oscillator
{
	TH0 = pitch_TH[pitch_pos];
	TL0 = pitch_TL[pitch_pos];
	SP = !SP;
}

void onTimer1() interrupt 3 // Speaker note timer
{
	TR1 = TR0 = 0; // SP OFF
}

void sp_play(u8 sound)
{
	//EX0 = 0;

	pitch_pos = sound;

	TH1 = TH_50MS;
	TL1 = TL_50MS;
	TR1 = 1;

	TH0 = pitch_TH[pitch_pos];
	TL0 = pitch_TL[pitch_pos];
	TR0 = 1;
}
void delayms(int time)
{

	u8 i = 0;
	while (time)
	{
		for (i = 120; i; i--)
			;
		time--;
	}
}
