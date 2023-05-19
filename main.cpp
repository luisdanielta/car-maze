#include <stdint.h>
#include "pico/stdlib.h"
#include "core.h"
#include "motor.h"
#include "control.h"

uint8_t pins_left[2] = {14, 13};
uint8_t pins_right[2] = {12, 11};

motor motor_left(pins_left);
motor motor_right(pins_right);

uint8_t en[2] = {15, 10};
control motors(motor_left, motor_right, en);

int main()
{
    stdio_init_all();
    mode_usb_debug(true);

    while (true)
    {
        motors.forward();
    }
    return 0;
}