#include "motor.h"

motor::motor(uint8_t *pins)
{
    for (int i = 0; i < 2; i++)
    {
        this->pins[i] = pins[i];
        gpio_init(this->pins[i]);
        gpio_set_dir(this->pins[i], GPIO_OUT);
    }
}

motor::~motor() {}
