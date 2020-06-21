#include "common.h"

void lcd_init();
void lcd_putLn(const char *ln);
void lcd_setCursor(u8 ln, u8 col);
void lcd_write(u8 instr);
