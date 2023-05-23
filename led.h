#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

class led
{
private:
    uint8_t set_brightness(uint8_t);

public:
    led(uint8_t);
    ~led();
    uint8_t pin;
    bool state;

    uint8_t brightness = 100;

    void toggle();
    void on();
    void off();
};

#endif // LED_H