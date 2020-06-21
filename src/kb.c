#include <AT89X52.H>
#include "../inc/kb.h"
#include "../inc/common.h"
#include "../inc/delay.h"

u8 kb_scan();

code u8 TH20MS = XTAL12_TH(20),
        TL20MS = XTAL12_TL(20);

u8 kb_r(void (*hold)(void *), void *hold_arg0)
{
    u8 scan_ret, i;

    scan_ret = kb_scan();

    if (!~scan_ret) // nothing is pressed
        return 0xff;

    // Delay
    for (i = 4; i; i--) hold(hold_arg0);
    
    if (kb_scan() == scan_ret)
    {
        // run hold function until key is released
        while (kb_scan() != 0xff)
            hold(hold_arg0);

        return scan_ret;
    }

    return 0xff;
}

u8 kb_scan()
{
    u8 col, row;

    for (col = 0; col < 4; col++)
    {
        P0 = ~(1 << (col + 4)); // set COLth to read

        for (row = 0; row < 4; row++)
            if (!(P0 >> row & 1)) //the ROWth bit is set
                return (3 - col) * 4 + row;
    }

    return 0xff;
}
