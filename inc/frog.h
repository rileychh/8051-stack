#include <AT89X52.H>

#ifndef FROG_H
#define FROG_H

#define SP P3_4
#define DOTM_R P2
#define DOTM_C P0

#define TH_50MS 60
#define TL_50MS 176

#ifdef __GNUC__
#define code const
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef char i8;
typedef short i16;

extern u8 delaycount = 0;
extern u8 pitch_pos = 0;

void scan_delay(u8 time);
void sp_init();
void sp_play(u8 sound); //0 means you loss one but didn't lose, 1 means you get the point perfectly, 2 means you lose
void dotm_put(u8 buf[8]);
void ssd_put(u8 num);

#endif // FROG_H

