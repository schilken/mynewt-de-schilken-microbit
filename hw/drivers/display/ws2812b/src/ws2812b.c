//
// Created by Alfred Schilken on 18.07.17.
//

#include "ws2812b/ws2812b.h"
#include "hal/hal_gpio.h"
#include "syscfg/syscfg.h"
#include "nrf51.h"

static grb_color_t _grb;


#define WS2812B_LED_PIN  (MYNEWT_VAL(WS2812B_LED_PIN))

void ws2812_init() {
    hal_gpio_init_out(WS2812B_LED_PIN, 0);
}

void rgb_set(uint8_t r, uint8_t g, uint8_t b) {
    _grb.asVars.r = r;
    _grb.asVars.g = g;
    _grb.asVars.b = b;
}

static void
nrf51_delay_us(uint32_t number_of_us)
{
    register uint32_t delay __ASM ("r0") = number_of_us;
    __ASM volatile (
    ".syntax unified\n"
            "1:\n"
            " SUBS %0, %0, #1\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " NOP\n"
            " BNE 1b\n"
            ".syntax divided\n"
    : "+r" (delay));
}


void rgb_send() {
    nrf51_delay_us(50);
    for (int j = 0; j < 3; j++) {
        if (_grb.asArray[j] & 0b10000000) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b01000000) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00100000) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00010000) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00001000) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00000100) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00000010) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }

        if (_grb.asArray[j] & 0b00000001) { WS2812B_SEND_ONE }
        else { WS2812B_SEND_ZERO }
    }
}



