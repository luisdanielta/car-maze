#include <stdint.h>
#include "pico/stdlib.h"
#include "core.h"
#include "motor.h"
#include "control.h"
#include <string>
#include "led.h"
#include "hardware/i2c.h"
#include "Servo.h"
#include "GFX.h"
#include <stdio.h>

/* MOTORS */
uint8_t pins_left[2] = {14, 13};
uint8_t pins_right[2] = {11, 12};

motor motor_left(pins_left);
motor motor_right(pins_right);

uint8_t en[2] = {15, 10}; // pin out of speed
control motors(motor_left, motor_right, en);

/* SENSORS OF LIGHT */
uint8_t SL_LEFT = 21;
uint8_t SL_RIGHT = 20;
void init_sl_sensors();

/* HC-SR04 */
const uint8_t TRIG_PIN = 27;
const uint8_t ECHO_PIN = 26;
void init_hc_sr04();
float measure_distance();
float calculate_speed(float, float, uint32_t);

/* SYSTEM */
led system_led(25);

/* SERVO */
Servo servo;

using namespace std;

int main()
{
    stdio_init_all();
    mode_usb_debug(true);

    /* HC-SR04 */
    init_hc_sr04();
    float tmp_distance[2];
    float current_distance;

    /* SENSORS OF LIGHT */
    void init_sl_sensors();
    bool sl_l_state;
    bool sl_r_state;

    /* SYSTEM */
    system_led.brightness = 50;
    system_led.on();

    /* SERVO */
    servo.attach(1);

    /* DISPLAY */
    i2c_init(i2c1, 400000);              // Initialize I2C on i2c1 port with 400kHz
    gpio_set_function(2, GPIO_FUNC_I2C); // Use GPIO2 as I2C
    gpio_set_function(3, GPIO_FUNC_I2C); // Use GPIO3 as I2C
    gpio_pull_up(2);                     // Pull up GPIO2
    gpio_pull_up(3);                     // Pull up GPIO3

    GFX oled(0x3C, size::W128xH64, i2c1); // Declare oled instance

    while (true)
    {
        sl_l_state = gpio_get(SL_LEFT);
        sl_r_state = gpio_get(SL_RIGHT);

        if (!sl_l_state && !sl_r_state)
        {
            motors.forward();
        }
        else if (sl_l_state && sl_r_state)
        {
            motors.stop();
            servo.write(0);
            current_distance = measure_distance();
            tmp_distance[0] = current_distance;
            sleep_ms(1000);

            servo.write(180);
            current_distance = measure_distance();
            tmp_distance[1] = current_distance;
            sleep_ms(1000);

            if (tmp_distance[0] > tmp_distance[1])
            {
                motors.right();
                motors.forward();
            }
            else if (tmp_distance[0] == tmp_distance[1])
            {
                motors.backward();
            }
            else
            {
                motors.left();
                motors.forward();
            }
        }
        else if (sl_l_state && !sl_r_state)
        {
            motors.left();
            motors.forward();
        }
        else if (!sl_l_state && sl_r_state)
        {
            motors.right();
            motors.forward();
        }
    }
    return 0;
}

/* func sensors of light */
void init_sl_sensors()
{
    gpio_init(SL_LEFT);
    gpio_init(SL_RIGHT);
    gpio_set_dir(SL_LEFT, GPIO_IN);
    gpio_set_dir(SL_RIGHT, GPIO_IN);
}

/* func hc-sr04 */
void init_hc_sr04()
{
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    gpio_set_pulls(ECHO_PIN, true, false);
}

float measure_distance()
{
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);

    while (!gpio_get(ECHO_PIN))
        ;

    uint32_t start_time = time_us_32();
    while (gpio_get(ECHO_PIN))
        ;
    uint32_t end_time = time_us_32();

    uint32_t pulse_duration = end_time - start_time;

    float distance = pulse_duration * 0.0343 / 2.0;

    return distance;
}

float calculate_speed(float d_uno, float d_two, uint32_t time_interval)
{
    float speed = (d_two - d_uno) / (time_interval / 1000000.0);
    return speed;
}