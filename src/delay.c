#include <AT89X52.H>
#include "../inc/delay.h"
#include "../inc/common.h"

void delay(u8 th, u8 tl)
{
    TMOD = 0x01;

    TH0 = th;
    TL0 = tl;

    TR0 = 1;
    while (!TF0)
        ;

    TF0 = 0;
    TR0 = 0;
}
