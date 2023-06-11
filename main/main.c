#include <esp_log.h>
#include <esp_err.h>
#include "i2c_master.h"
#include "adxl345.h"
#include "wifi.h"

static const char *TAG = "ESP32_flag_accel";

void app_main(void)
{
        uint8_t wifi_ssid[32] = "fat-man";
        uint8_t wifi_password[64] = "091102IAUG45";

        ESP_ERROR_CHECK(i2c_master_init());
        ESP_LOGI(TAG, "I2C initialized successfully.");

        ESP_ERROR_CHECK(adxl345_init());
        ESP_LOGI(TAG, "ADXL345 accelerometer initialized successfully.");

        ESP_ERROR_CHECK(wifi_connect(wifi_ssid, wifi_password));
        ESP_LOGI(TAG, "Wi-Fi connection established successfully.");
}
