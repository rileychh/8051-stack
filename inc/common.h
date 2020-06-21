#ifndef COMMON_H
#define COMMON_H

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef char i8;
typedef int i16; // same as short
typedef long i32;
typedef float f32; // same as double

#ifdef __GNUC__
#define code const
#endif

void arr_shift(u8 *arr, u8 len, u8 new_item, u8 right);

#endif
