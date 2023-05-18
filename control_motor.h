#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor.h"

class control_motor
{
private:
    motor &motor_left;
    motor &motor_right;
    uint8_t en[2];

public:
    control_motor(motor &, motor &, uint8_t *);
    ~control_motor();
    void forward();
    void backward();
    void stop();
    void left();
    void right();
};

#endif // MOTOR_CONTROL_H
