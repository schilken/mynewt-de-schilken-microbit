//
// Created by Alfred Schilken on 19.07.17.
//

#include <assert.h>
#include "sysinit/sysinit.h"
#include "os/os.h"
#include "hal/hal_gpio.h"
#include "bsp/bsp.h"
#include <console/console.h>

/* The timer callout */
static struct os_callout timer_callout;

#if MYNEWT_VAL(BUTTON_B_ENABLED)
static uint16_t button_A_state = 0;
#endif

static struct os_event button_irq_event = {
        .ev_cb = NULL, // has to be set by application using microbit_set_button_cb()
        .ev_arg = NULL
};

static void timer_ev_cb(struct os_event *ev)
{
    assert(ev != NULL);
    button_A_state = (button_A_state << 1) | hal_gpio_read(BUTTON_A_PIN) | 0xe000;
    if(button_A_state == 0xf000) {
        button_irq_event.ev_arg = (void*)BUTTON_A_PIN;
        os_eventq_put(os_eventq_dflt_get(), &button_irq_event);
    }
//    os_callout_reset(&timer_callout, (OS_TICKS_PER_SEC));
    os_callout_reset(&timer_callout, (6 * OS_TICKS_PER_SEC)/1000);
}

static void init_timer(void)
{
    /*
     * Initialize the callout for a timer event.
     */
    os_callout_init(&timer_callout, os_eventq_dflt_get(),
                    timer_ev_cb, NULL);
    os_callout_reset(&timer_callout, (6 * OS_TICKS_PER_SEC)/1000);
}

void microbit_set_button_cb(os_event_fn *ev_cb) {
    hal_gpio_init_in(BUTTON_A_PIN, HAL_GPIO_PULL_UP);
    button_irq_event.ev_cb = ev_cb;
    init_timer();
}