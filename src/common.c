#include "../inc/common.h"

void arr_shift(u8 *arr, u8 len, u8 new_item, u8 right)
{
    u8 i;

    for (i = 0; i < len - 1; i++)
        arr[i + right] = arr[i + !right];
        
    arr[right ? 0 : len - 1] = new_item;
}
