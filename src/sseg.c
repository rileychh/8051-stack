/* 
 *  sseg.c
 *  Functions for 7-segment display on TE-8051A.
 *  By Chengxuan He.
 */

#include <AT89X52.H>
#include <string.h>
#include "../inc/sseg.h"
#include "../inc/common.h"
#include "../inc/delay.h"

#define TH1MS XTAL12_TH(1)
#define TL1MS XTAL12_TL(1)

// "decoder"
code u8 sseg_dec[] = {
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71,
    0x00, 0x80, 0x39, 0x0f};

code u8 __NO_RAW[] = {0, 0, 0, 0, 0, 0, 0, 0};

void sseg_put(u8 f_buf[8], u8 raw[8])
{
    u8 i;

    /*
     *  P1: Displays' common pins. Changes current lit display.
     *  P2: Displays' a, b, c, d, e, f, g, dp pins. Changes current lit segment.
     */
    for (i = 0, P1 &= 0xf8, P2 = 0; i < 8; i++, P1++, P2 = 0)
    {
        P2 = sseg_dec[f_buf[i]] | raw[i];
        delay(TH1MS, TL1MS);
        if (i == 7)
            break;
    }
}

void sseg_slide(u8 f_bufs[][8], u8 len, u8 delay)
{
    u8 i, j;

    for (i = 0; i < len; i++)
        for (j = delay; j; j--)
            sseg_put(f_bufs[i], __NO_RAW);
}

void sseg_scroller(u8 infos[], u8 len, u8 delay, u8 hold, u8 to_left)
{
    u8 f_buf[8], i, j,
        count = to_left && len < 8 ? 8 : len;

    memset(f_buf, SSEG_OFF, 8);

    for (i = 0; i < count; i++)
    {
        arr_shift(f_buf, 8, i >= len ? 0x10 : infos[i], 0);

        for (j = delay; j; j--)
            sseg_put(f_buf, __NO_RAW);
    }

    for (i = hold; i; i--)
        sseg_put(f_buf, __NO_RAW);
}
