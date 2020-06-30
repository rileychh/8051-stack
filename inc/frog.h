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

void sp_init();

void dotm_put(u8 buf[8]);

#endif // FROG_H

