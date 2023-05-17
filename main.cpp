#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include <math.h>
#include <string>
#include "pico/multicore.h"

void reload_program();
bool reload_pin_previous = true;
#define RELOAD_PIN 16

/* HC-SR04 */
const uint8_t TRIG_PIN = 27;
const uint8_t ECHO_PIN = 26;
void init_hc_sr04();
float measure_distance();
float calculate_speed(float, float, uint32_t);

/* HM-sensors */
const uint8_t LET_HM = 9;
const uint8_t RIGHT_HM = 21;

/* motors */

using namespace std;

int main()
{
    stdio_init_all();

    /* two core */
    multicore_launch_core1(reload_program);

    gpio_init(RELOAD_PIN);
    gpio_set_dir(RELOAD_PIN, GPIO_IN);
    gpio_pull_up(RELOAD_PIN);

    /* HC-SR04 */
    init_hc_sr04();

    /* HM-sensors */
    gpio_init(LET_HM);
    gpio_set_dir(LET_HM, GPIO_IN);
    gpio_init(RIGHT_HM);
    gpio_set_dir(RIGHT_HM, GPIO_IN);

    /* test */
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);

    while (true)
    {
        bool let = gpio_get(LET_HM);
        // string str_let = to_string(let);
        // printf("%s", str_let.c_str());

        if (!let)
            gpio_put(22, true);
        else
            gpio_put(22, false);
        
        float current_distance = measure_distance();
        printf("Distance: %.2f cm\n", current_distance);


        sleep_ms(1000);

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
    while (true)
    {
        bool reload_pin_current = !gpio_get(RELOAD_PIN);
        if (reload_pin_current && !reload_pin_previous)
            reset_usb_boot(0, 0);
        reload_pin_previous = reload_pin_current;
    }
    multicore_reset_core1();
}