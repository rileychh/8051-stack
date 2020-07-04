#include <stdio.h>

#define u8 unsigned char

u8 dotm_buf[8];
u8 currLine = 0;

int main()
{
    while (1)
    {
        for (int i = 0; i < 8; i++)
            dotm_buf[i] = 0x0;
        dotm_buf[7 - currLine] = 0x7e;
        currLine++;
        printf("%s",&dotm_buf[currLine]);
    }
}