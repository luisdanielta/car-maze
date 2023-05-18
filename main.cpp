#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"
#include "motor.h"
#include "control_motor.h"

void reload_program();
bool reload_pin_previous = true;
#define RELOAD_PIN 16

uint8_t motor_l_p[2] = {14, 13};
motor motor_left(motor_l_p);

uint8_t motor_r_p[2] = {11, 12};
motor motor_right(motor_r_p);

uint8_t en[2] = {15, 10};
control_motor motors(motor_left, motor_right, en);

/* HM-sensors */
const uint8_t LET_HM = 9;

int main()
{
    stdio_init_all();

    gpio_init(RELOAD_PIN);
    gpio_set_dir(RELOAD_PIN, GPIO_IN);
    gpio_pull_up(RELOAD_PIN);

    gpio_init(20);
    gpio_set_dir(20, GPIO_IN);
    gpio_pull_up(20);

    gpio_init(LET_HM);
    gpio_set_dir(LET_HM, GPIO_IN);


    while (true)
    {
        reload_program();

        bool let = gpio_get(LET_HM);

        if (let)
            motors.forward();
        else
            motors.stop();

        /*
         stop control with button 20 is pressed and change state
         with again pressed button 20
        */
    }

    return 0;
}

void reload_program()
{
    /*
        The reload_program function is designed to check
        the state of a specific pin (RELOAD_PIN) and initiate
        a USB boot mode if a certain condition is met.
    */

    bool reload_pin_current = !gpio_get(RELOAD_PIN);
    if (reload_pin_current && !reload_pin_previous)
        reset_usb_boot(0, 0);
    reload_pin_previous = reload_pin_current;
}