#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "pico/stdlib.h"

class motor
{
public:
    motor(uint8_t *);
    ~motor();
    uint8_t pins[2];
};

#endif // MOTOR_H
