#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <stdio.h>

class motor
{
private:
    uint8_t IN1;
    uint8_t IN2;
    uint8_t IN3;
    uint8_t IN4;

public:
    motor(uint8_t, uint8_t, uint8_t, uint8_t);
};

#endif