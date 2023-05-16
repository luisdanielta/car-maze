#include "motor_control.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"


motor::motor(uint8_t d_pins[])
{
    for (size_t i = 0; i <= EN; i++)
        PINS[i] = d_pins[i];

    for (size_t j = 0; j <= EN; j++)
    {
        gpio_init(PINS[j]);
        gpio_set_dir(PINS[j], GPIO_OUT);
    }



}

void motor::stop()
{
    for (size_t i = 0; i <= EN; i++)
        gpio_put(PINS[i], false);
}