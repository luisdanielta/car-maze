#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include <math.h>

void reload_program();
bool reload_pin_previous = true;
#define RELOAD_PIN 16

/* HC-SR04 */
const uint8_t TRIG_PIN = 27;
const uint8_t ECHO_PIN = 26;
void init_hc_sr04();
float measure_distance();
float calculate_speed(float, float, uint32_t);

int main()
{
    stdio_init_all();

    gpio_init(RELOAD_PIN);
    gpio_set_dir(RELOAD_PIN, GPIO_IN);
    gpio_pull_up(RELOAD_PIN);

    /* HC-SR04 */
    init_hc_sr04();

    float previous_distance = 0.0;
    uint32_t previous_time = time_us_32();

    while (true)
    {
        reload_program();

        float current_distance = measure_distance();
        uint32_t current_time = time_us_32();

        float speed = calculate_speed(previous_distance, current_distance, current_time - previous_time);
        printf("Speed: %.2f cm/s\n", abs(speed));
        printf("Distance: %.2f cm\n", current_distance);

        previous_distance = current_distance;
        previous_time = current_time;

        sleep_ms(300);
    }

    return 0;
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

/* func extras */
void reload_program()
{
    /*
        The reload_program function is designed to check
        the state of a specific pin (RELOAD_PIN) and initiate
        a USB boot mode if a certain condition is met.
    */
    bool reload_pin_current = !gpio_get(RELOAD_PIN);
    if (reload_pin_current && !reload_pin_previous)
        reset_usb_boot(0, 0);
    reload_pin_previous = reload_pin_current;
}