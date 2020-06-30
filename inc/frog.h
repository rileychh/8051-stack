#include <AT89X52.H>

#ifndef FROG_H
#define FROG_H

#define SP P3_4
#define DOTM_R P2
#define DOTM_C P0

#define TH_50MS 60
#define TL_50MS 176

typedef unsigned char u8;
typedef unsigned short u16;
typedef char i8;
typedef short i16;

void scan_delay(u8 time);
void sp_init();
u8 sp_play(u8 sound); //0 means you loss one but didn't lose, 1 means you get the point perfectly, 2 means you lose
void dotm_put(u8 buf[8]);
void ssd_put(u8 buf[2])

#endif // FROG_H

