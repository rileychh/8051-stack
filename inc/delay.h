#ifndef DELAY_H
#define DELAY_H

#include "common.h"

// https://www.electronicwings.com/8051/8051-timers
#define XTAL12_TH(ms) (((0x10000 - ms * 1000) >> 8) & 0xff)
#define XTAL12_TL(ms) (((0x10000 - ms * 1000) >> 0) & 0xff)
#define XTAL12_TH_MAX 0
#define XTAL12_TL_MAX 0

void delay(u8 th, u8 tl);

#endif
