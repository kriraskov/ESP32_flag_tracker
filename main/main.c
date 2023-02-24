#include <esp_log.h>
#include <esp_err.h>
#include "i2c_master.h"
#include "adxl345.h"

static const char *TAG = "ESP32_flag_accel";

void app_main(void)
{
        ESP_ERROR_CHECK(i2c_master_init());
        ESP_LOGI(TAG, "I2C initialized successfully");

        ESP_ERROR_CHECK(adxl345_init());
        ESP_LOGI(TAG, "ADXL345 accelerometer initialized successfully.");
}
