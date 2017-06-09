#ifndef MYPROJ_SSD1306_I2C_H
#define MYPROJ_SSD1306_I2C_H

#include <stdio.h>
#include <stdint.h>
#include <nrf51.h>

extern int init_oled();
extern int printAtXY(uint8_t x, uint8_t y, const char s[]);
extern int clear_screen(void);

#define DISPLAY_WIDTH	128
#define DISPLAY_HEIGHT	64
#define DISPLAYSIZE		DISPLAY_WIDTH*DISPLAY_HEIGHT/8	// 8 pages/lines with 128
// 8-bit-column: 128*64 pixel
// 1024 bytes


#endif