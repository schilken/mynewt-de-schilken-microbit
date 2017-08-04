//
// Created by Alfred Schilken on 25.05.17.
//

#include "syscfg/syscfg.h"
#include <shell/shell.h>
#include <console/console.h>
#include <assert.h>
#include <stdio.h>

static int adc_loop_cmd(int argc, char **argv);
static int adc_poll_cmd(int argc, char **argv);

#define ADC_MODULE "adc"

/*
 * Initialize param and command help information if SHELL_CMD_HELP
 * is enabled.
 */

#if MYNEWT_VAL(SHELL_CMD_HELP)
static const struct shell_param adc_loop_params[] = {
    {"", "on/off 0|1"},
    {NULL, NULL}
};

static const struct shell_cmd_help adc_loop_help = {
    .summary = "adc loop",
    .usage = NULL,
    .params = adc_loop_params,
};


static const struct shell_cmd_help adc_poll_help = {
    .summary = "adc poll",
    .usage = NULL,
    .params = NULL,
};

#endif

/*
 * Initialize an array of shell_cmd structures for the commands
 * in the adc module.
 */
static const struct shell_cmd adc_module_commands[] = {
    {
        .sc_cmd = "loop",
        .sc_cmd_func = adc_loop_cmd,
#if MYNEWT_VAL(SHELL_CMD_HELP)
        .help = &adc_loop_help,
#endif
    },
    {
        .sc_cmd = "poll",
        .sc_cmd_func = adc_poll_cmd,
#if MYNEWT_VAL(SHELL_CMD_HELP)
        .help = &adc_poll_help,
#endif
    },
    { NULL, NULL, NULL },
};


void
adc_commands_init(void)
{
    int rc = shell_register(ADC_MODULE, adc_module_commands);
    assert(rc == 0);
}


static int
adc_poll_cmd(int argc, char **argv) {
    console_printf("%d \n", argc);
    return 0;
}

static int
adc_loop_cmd(int argc, char **argv) {
    int onOff = 0;
    if (argc != 2) {
        console_printf("usage: adc loop 0|1\n");
        return 1;
    }
    if (sscanf( argv[1], "%d", &onOff) != 1) {
        if(onOff != 0 && onOff != 1) {
            console_printf("0 für OFF, 1 für ON\n");
            return 1;
        }
    }
    console_printf("adc: poll %s\n", onOff == 1 ? "ON" : "OFF");
    return 0;
}
