#include "motor_control.h"
#include "pico/stdlib.h"

motor::motor(u_int8_t pin_1, u_int8_t pin_2, u_int8_t pin_3, u_int8_t pin_4)
{
    uint8_t pins[4] = {IN1 = pin_1, IN2 = pin_2, IN3 = pin_3, IN4 = pin_4};

    for (int i = 0; i <= 4; i++)
    {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], GPIO_OUT);
    }
}