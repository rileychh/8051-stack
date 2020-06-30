#include <AT89X52.H>
#include "../inc/frog.h"
#define SSD_BLANK 0x00

// LSB = SEL, default is 0. +1 to show on second display.
code u8 SSD_DEC[] = {
    0xfc, 0x60, 0xda, 0xf2, 0x66,  // 0 ~ 4
    0xb6, 0xbe, 0xe4, 0xfe, 0xf6}; // 5 ~ 9

void ssd_put(u8 num)
{
    u8 digit = num / 10, i;

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            SSD = SSD_BLANK; break;
        case 1:
            // if tens isn't 0 then show, else blank
            SSD = digit ? SSD_DEC[digit] : SSD_BLANK; break;
        case 2:
            digit /= 10;
            SSD = SSD_DEC[digit];
            break;
        }
        scan_delay(1);
    }
}