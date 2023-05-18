#include "control_motor.h"

control_motor::control_motor(motor &motor_left, motor &motor_right, uint8_t *en)
    : motor_left(motor_left), motor_right(motor_right)
{
    for (int i = 0; i < 2; i++)
    {
        this->en[i] = en[i];
        gpio_init(this->en[i]);
        gpio_set_dir(this->en[i], GPIO_OUT);
    }

    gpio_put(this->en[0], 1);
    gpio_put(this->en[1], 1);

}

control_motor::~control_motor() {}

void control_motor::forward()
{
    gpio_put(motor_left.pins[0], 1);
    gpio_put(motor_left.pins[1], 0);
    gpio_put(motor_right.pins[0], 1);
    gpio_put(motor_right.pins[1], 0);
}

void control_motor::stop()
{
    gpio_put(motor_left.pins[0], 0);
    gpio_put(motor_left.pins[1], 0);
    gpio_put(motor_right.pins[0], 0);
    gpio_put(motor_right.pins[1], 0);
}