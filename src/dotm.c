#include <AT89X52.H>
#include "../inc/frog.h"

void dotm_scan_delay(u8 time);

void dotm_put(u8 buf[8])
{
    u8 y;

    for (y = 0; y < 8; y++)
    {
        DOTM_R = buf[y];
        DOTM_C = 1 << (7 - y);
        dotm_scan_delay(1);
    }
}

void dotm_scan_delay(u8 time)
{
    u8 i;

    while (time)
    {
        for (i = 120; i; i--);
        time--;
    }
}

