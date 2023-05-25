#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define VERSION 1 // Library version
#define MIN_PULSE_WIDTH 544 // Min. pulse width sent to a servo
#define MAX_PULSE_WIDTH 2400 // Max. pulse width sent to a servo
#define MIN_ANGLE 0 // Min. angle the servo can rotate to
#define MAX_ANGLE 180 // Max. angle the servo can rotate to
#define PRESCALER 64 // The prescaler used to control the servos
#define DEFAULT_FREQUENCY 50.f // Set the default pulse frequency to 50Hz (20ms period)
#define NOT_ATTACHED 32 // Constant used when the servo is not attached to any gpio pin

class Servo {
  public:
    Servo();
    void attach(uint gpio, uint min_pulse = MIN_PULSE_WIDTH, uint max_pulse = MAX_PULSE_WIDTH);
    void detach();
    void write(uint value);
    void writeMicroseconds(uint value);
    uint read();
    uint readMicroseconds();
    bool attached() const { return this->gpio != NOT_ATTACHED; }
  private:
    uint gpio;
    uint min_pulse;
    uint max_pulse;
    uint current_pulse;
    uint slice;
    uint channel;
    void resetFields();
};
#endif