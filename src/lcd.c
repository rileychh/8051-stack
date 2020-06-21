#include <AT89X51.H>
#include "../inc/lcd.h"
#include "../inc/common.h"
#include "../inc/delay.h"

#define RS P1_0
#define RW P1_1
#define E P1_2
#define DB P2

#define TH1MS XTAL12_TH(1)
#define TL1MS XTAL12_TL(1)

void lcd_init() {
    lcd_write(0x38);
}

void lcd_putLn(const char *ln) {

}

void lcd_setCursor(u8 ln, u8 col) {

}

void lcd_write(u8 instr) {

}

