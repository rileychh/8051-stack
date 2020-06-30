#include <AT89X52.H>
#include "../inc/frog.h"

// LSB = SEL, default is 0. +1 to show on second display.
code u8 ssd_dec[] = {
    0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe4}; // TODO　undone

void ssd_put(u8 num)
{
    scan_delay(1);
}