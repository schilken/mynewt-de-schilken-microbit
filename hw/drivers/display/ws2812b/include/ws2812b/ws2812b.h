//
// Created by Alfred Schilken on 18.07.17.
//

#ifndef MYPROJ_WS2812B_H
#define MYPROJ_WS2812B_H

#include <stdint.h>

extern void ws2812_init();
extern void rgb_set(uint8_t r, uint8_t g, uint8_t b);
extern void rgb_send();

// map separate vars g, r and b to an array with 3 bytes
typedef union {
    struct {
        uint8_t g, r, b;
    }asVars;
    uint8_t asArray[3];
} grb_color_t;

//These defines are timed specific to a series of if statements and will need to be changed
//to compensate for different writing algorithms than the one in neopixel.c
#define WS2812B_SEND_ONE	NRF_GPIO->OUTSET = (1UL << WS2812B_LED_PIN); \
			__ASM ( \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
				); \
			NRF_GPIO->OUTCLR = (1UL << WS2812B_LED_PIN); \


#define WS2812B_SEND_ZERO NRF_GPIO->OUTSET = (1UL << WS2812B_LED_PIN); \
			__ASM (  \
					" NOP\n\t"  \
				);  \
			NRF_GPIO->OUTCLR = (1UL << WS2812B_LED_PIN);  \
			__ASM ( \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
					" NOP\n\t" \
				);

#endif //MYPROJ_WS2812B_H
