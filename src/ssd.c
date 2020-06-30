#include <AT89X52.H>
#include "../inc/frog.h"

// LSB = SEL, default is 0. +1 to show on second display.
code u8 ssd_dec[] = {
    0xfc, 0x60 }; // TODO　undone

void ssd_put(u8 num)
{
    scan_delay(1);
}