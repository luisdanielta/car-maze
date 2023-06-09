#include <stdint.h>
#include "pico/stdlib.h"
#include "core.h"
#include "motor.h"
#include "control.h"
#include <string>
#include "led.h"

/* MOTORS */
uint8_t pins_left[2] = {14, 13};
uint8_t pins_right[2] = {11, 12};

motor motor_left(pins_left);
motor motor_right(pins_right);

uint8_t en[2] = {15, 10}; // pin out of speed
control motors(motor_left, motor_right, en);

/* SENSORS OF LIGHT */
uint8_t SL_LEFT = 9;
uint8_t SL_RIGHT = 22;
void init_sl_sensors();

/* HC-SR04 */
const uint8_t TRIG_PIN = 27;
const uint8_t ECHO_PIN = 26;
void init_hc_sr04();
float measure_distance();
float calculate_speed(float, float, uint32_t);

/* SYSTEM */
led system_led(25);

using namespace std;

int main()
{
    stdio_init_all();
    mode_usb_debug(true);

    /* HC-SR04 */
    init_hc_sr04();

    /* SENSORS OF LIGHT */
    void init_sl_sensors();

    /* SYSTEM */
    system_led.brightness = 50;
    system_led.on();

    while (true)
    { 
        bool sl_l_state = gpio_get(SL_LEFT);
        string str_let = to_string(sl_l_state);
        printf("%s", str_let.c_str());
        
        if (!sl_l_state)
            motors.forward();
        else
            motors.stop();
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