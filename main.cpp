#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include <stdint.h>
#include "motor.h"
#include "control_motor.h"

void reload_program();
bool reload_pin_previous = true;
#define RELOAD_PIN 16

uint8_t pins_left[2] = {14, 13};
uint8_t pins_right[2] = {12, 11};

motor motor_left(pins_left);
motor motor_right(pins_right);

uint8_t en[2] = {15, 10};
control_motor motors(motor_left, motor_right, en);

int main()
{
    stdio_init_all();

    gpio_init(RELOAD_PIN);
    gpio_set_dir(RELOAD_PIN, GPIO_IN);
    gpio_pull_up(RELOAD_PIN);

    while (true)
    {
        reload_program();
        motors.forward();
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