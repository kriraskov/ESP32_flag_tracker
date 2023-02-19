#include <esp_log.h>
#include "driver/i2c.h"
#include "i2c_master.h"
#include "adxl345.h"
#include "driver/gpio.h"

static const char *TAG = "ESP32_flag_accel";

_Noreturn void app_main(void) {
        int16_t ax, ay, az;

        ESP_ERROR_CHECK(i2c_master_init());
        ESP_LOGI(TAG, "I2C initialized successfully");

        ESP_ERROR_CHECK(adxl345_i2c_slave_init());
        ESP_LOGI(TAG, "ADXL345 accelerometer initialized successfully.");

        while (1) {
                adxl345_read_data(&ax, &ay, &az);

                printf("--- Acceleration: ---\n");
                printf("x-axis: %f g\n", (float) ax / 0x0FFF);
                printf("y-axis: %f g\n", (float) ay / 0x0FFF);
                printf("z-axis: %f g\n", (float) az / 0x0FFF);
        }

        ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
        ESP_LOGI(TAG, "I2C de-initialized successfully");
}
