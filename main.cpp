#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "core.h"

int main() {
    stdio_init_all(); // Inicializar las funciones de la biblioteca stdio
    mode_usb_debug(true); // Modo de depuración USB

    // Configurar los pines SDA y SCL
    i2c_init(i2c0, 400000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    // Escanear dispositivos I2C
    printf("Escaneando dispositivos I2C...\n");

    for (uint8_t address = 0; address <= 127; ++address) {
        uint8_t result = i2c_write_blocking(i2c0, address, NULL, 0, true);
        if (result == PICO_ERROR_GENERIC) {
            printf("Dispositivo encontrado en dirección 0x%02X\n", address);
        }
    }

    return 0;
}
