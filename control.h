#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "motor.h"

class control
{
private:
    motor &motor_left;
    motor &motor_right;
    
    uint8_t en[2];
    bool FORWARD = true;
    bool STOP = false;
    uint8_t HIGH[5] = {0, 64, 128, 192, 255};
    uint8_t LOW[5] = {255, 192, 128, 64, 0};
    int speed(uint8_t *);
    
    uint8_t LIGHTS[2];
    void left_turn_signals();
    void right_turn_signals();

public:
    control(motor &, motor &, uint8_t *);
    ~control();
    
    /* movement */
    void forward();
    void backward();
    void stop();

    /* lights */
    void set_turn_signals(uint8_t *);
};

#endif // MOTOR_CONTROL_H
