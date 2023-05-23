#include "led.h"

led::led(uint8_t pin)
{
    this->pin = pin;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_set_function(this->pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(this->pin);
    pwm_config config = pwm_get_default_config();

    pwm_init(slice_num, &config, true);
    pwm_set_wrap(slice_num, 255);

    pwm_set_gpio_level(this->pin, set_brightness(brightness));

    this->state = false;
}

led::~led() {}

uint8_t led::set_brightness(uint8_t brightness)
{
    return (brightness * 255) / 100;
}

void led::on()
{
    this->state = true;
    pwm_set_gpio_level(this->pin, set_brightness(brightness));
}

void led::off()
{
    this->state = false;
    pwm_set_gpio_level(this->pin, 0);
}

void led::toggle()
{
    state ? off() : on();
}