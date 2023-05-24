#ifndef CORE_H
#define CORE_H
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico/multicore.h"

void reload_program();
void mode_usb_debug(bool);

#endif