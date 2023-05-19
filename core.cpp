#include "core.h"

#define RELOAD_PIN 16
bool reload_pin_previous = true;

void mode_usb_debug(bool mode)
{
    if (mode)
        multicore_launch_core1(reload_program);
}

void reload_program()
{

    gpio_init(RELOAD_PIN);
    gpio_set_dir(RELOAD_PIN, GPIO_IN);
    gpio_pull_up(RELOAD_PIN);

    /*
        The reload_program function is designed to check
        the state of a specific pin (RELOAD_PIN) and initiate
        a USB boot mode if a certain condition is met.
    */
    while (true)
    {
        bool reload_pin_current = !gpio_get(RELOAD_PIN);
        if (reload_pin_current && !reload_pin_previous)
            reset_usb_boot(0, 0);
        reload_pin_previous = reload_pin_current;
    }
    multicore_reset_core1();
}