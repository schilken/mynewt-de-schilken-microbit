//
// Created by Alfred Schilken on 25.05.17.
//

#include "syscfg/syscfg.h"
#include <shell/shell.h>
#include <console/console.h>
#include <assert.h>
#include <stdio.h>
#include "hal/hal_gpio.h"

static int gpio_scan_cmd(int argc, char **argv);
static int gpio_write_cmd(int argc, char **argv);

#define GPIO_MODULE "gpio"

/*
 * Initialize param and command help information if SHELL_CMD_HELP
 * is enabled.
 */

#if MYNEWT_VAL(SHELL_CMD_HELP)
static const struct shell_param gpio_write_params[] = {
    {"", "pin"},
    {"", "value"},
    {NULL, NULL}
};

static const struct shell_cmd_help gpio_write_help = {
    .summary = "write to gpio",
    .usage = NULL,
    .params = gpio_write_params,
};


static const struct shell_cmd_help gpio_scan_help = {
    .summary = "scan calliope gpios",
    .usage = NULL,
    .params = NULL,
};

#endif

/*
 * Initialize an array of shell_cmd structures for the commands
 * in the gpio module.
 */
static const struct shell_cmd gpio_module_commands[] = {
    {
        .sc_cmd = "w",
        .sc_cmd_func = gpio_write_cmd,
#if MYNEWT_VAL(SHELL_CMD_HELP)
        .help = &gpio_write_help,
#endif
    },
    {
        .sc_cmd = "scan",
        .sc_cmd_func = gpio_scan_cmd,
#if MYNEWT_VAL(SHELL_CMD_HELP)
        .help = &gpio_scan_help,
#endif
    },
    { NULL, NULL, NULL },
};


void
gpio_commands_init(void)
{
    int rc = shell_register(GPIO_MODULE, gpio_module_commands);
    assert(rc == 0);
}

#ifdef BBC_MICROBIT
int8_t gpio_mapping[21] = {
        3,
        2,
        1,
        4,
        5,
        17,
        12,
        11,
        18,
        10,
        6,
        26,
        20,
        23,
        22,
        21,
        16,
        -1,
        -1,
        0,
        30
};

int getPinFromGpioPin(int8_t gpioPin){
    int8_t pin = -1;
    int8_t numPins = sizeof(gpio_mapping);
    for(pin = 0; pin < numPins; pin++){
        if(gpio_mapping[pin] == gpioPin){
            break;
        }
    }
    return pin < numPins ? pin : -1;
}
#endif


static int
gpio_scan_cmd(int argc, char **argv) {
    console_printf("%d \n", argc);
    return 0;
}

static int
gpio_write_cmd(int argc, char **argv) {
    int onOff;
    int gpio_pin=-1;
    char* pin;
    if (argc != 3) {
        console_printf("usage: gpio w <pin> <onOff>, <pin>: p0..p30, onOff: 0 oder 1\n");
        return 1;
    }
    pin = argv[1];
    if (*pin != 'P' && *pin != 'p') {
        console_printf("<pin>: p0..p30\n");
        return 1;
    }
#ifdef BBC_MICROBIT
    if (sscanf(pin, "P%d", &pin_nr) == 1) {
        if(pin_nr < 0 || pin_nr > 20) {
            console_printf("Board-PIN: 0 bis 20\n");
            return 1;
        }
        gpio_pin = gpio_mapping[pin_nr];
    }
#endif
    if (sscanf( pin, "p%d", &gpio_pin) == 1) {
        if(gpio_pin < 0 || gpio_pin > 30) {
            console_printf("CPU-pin: 0 bis 30\n");
            return 1;
        }
#ifdef BBC_MICROBIT
        int pin_nr = getPinFromGpioPin((int8_t)gpio_pin);
#endif
    }
    if (sscanf( argv[2], "%d", &onOff) != 1) {
        if(onOff != 0 && onOff != 1) {
            console_printf("0 für LOW(0V), 1 für HIGH (3V)\n");
            return 1;
        }
    }
#ifdef BBC_MICROBIT
    console_printf("gpio: P%d(p%d) %s\n", pin_nr, gpio_pin, onOff == 0 ? "LOW" : "HIGH");
#else
    console_printf("gpio: p%d %s\n", gpio_pin, onOff == 0 ? "LOW" : "HIGH");
#endif
//    hal_gpio_init_out(gpio_pin, onOff);
    return 0;
}
