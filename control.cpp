#include "control.h"
#include "hardware/pwm.h"

control::control(motor &motor_left, motor &motor_right, uint8_t *en)
    : motor_left(motor_left), motor_right(motor_right)
{
    /* set config pin of en(set speed) PWM */
    uint slice_num[2];
    pwm_config config = pwm_get_default_config();

    for (size_t i = 0; i < 2; i++)
    {
        this->en[i] = en[i];
        gpio_init(this->en[i]);
        gpio_set_dir(this->en[i], GPIO_OUT);
        gpio_set_function(this->en[i], GPIO_FUNC_PWM);
        slice_num[i] = pwm_gpio_to_slice_num(this->en[i]);
        pwm_init(slice_num[i], &config, true);
        pwm_set_wrap(slice_num[i], 255);
        pwm_set_gpio_level(this->en[i], 0);
    }
}

control::~control() {}

int control::speed(uint8_t *speed)
{
    size_t i;
    for (i = 0; i < 5; i++)
    {
        pwm_set_gpio_level(this->en[0], speed[i]);
        pwm_set_gpio_level(this->en[1], speed[i]);
        sleep_ms(300);
    }
    return i;
}











void control::forward()
{
    gpio_put(motor_left.pins[0], 1);
    gpio_put(motor_left.pins[1], 0);

    gpio_put(motor_right.pins[0], 1);
    gpio_put(motor_right.pins[1], 0);

    if (FORWARD) // check if the motor is already
    {
        int status = speed(HIGH);
        if (status == 5)
        {
            FORWARD = false; // disable accelerate
            STOP = true;     // enable stop
        }
    }
    else
        pwm_set_gpio_level(this->en[0], 255); // set speed to max
}

void control::stop()
{
    if (STOP)
    {
        int status = speed(LOW); // decelerate
        if (status == 5)
        {
            FORWARD = true; // enable accelerate
            STOP = false;   // disable stop
        }
    }
}