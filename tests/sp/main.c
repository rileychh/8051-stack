#include <AT89X52.H>
#include "../../inc/frog.h"

void main()
{
    u16 i;

    for (;;)
    {
        SP = !SP;
        for (i = 1250; i; i--)
            ;
    }
}
