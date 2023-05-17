#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdio.h>
#include "motor.h"

class control: public motor
{
private:
    uint8_t EN; // enable number of pins, default 4
    /* IN1 IN2 IN3 IN4 ENA(optional) ENB(optional) */
    uint8_t PINS[5];

    /* speed */
    void speed(uint8_t *);
    uint8_t HIGH[5] = {51, 102, 153, 204, 254};
    uint8_t LOW[5] = {204, 153, 102, 51, 0};

public:
    control(uint8_t *);
    void stop();
};

#endif