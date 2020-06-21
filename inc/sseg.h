#ifndef SSEG_H
#define SSEG_H

#include "common.h"

#define SSEG_OFF 0x10
#define SSEG_DOT 0x11
#define SSEG_LB  0x12
#define SSEG_RB  0x13

/*  Common Cathode 7-Segment display print function
 *  Input: sseg_slide({0xa, 0xb, 0x1, 0x2}, 4)
 *  Output: [    AB12] on the 7-segment display
 *  
 *  info: array of 8 unsigned integers, display data.
 *  len: an unsigned integer, length of info, max 8.
 */
void sseg_put(u8 f_buf[8], u8 raw[8]);

/*
 * TODO add desc
 */
void sseg_slide(u8 arr_infos[][8], u8 arr_len, u8 delay);

/*
 * TODO add desc
 */
void sseg_scroller(u8 infos[], u8 len, u8 delay, u8 hold, u8 to_left);

#endif
