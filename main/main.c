#include <esp_wifi.h>
#include <esp_log.h>
#include "nvs_flash.h"
#include "i2c_master.h"
#include "adxl345.h"
#include "wifi.h"

static const char *TAG = "ESP32_flag_accel";

void app_main(void)
{
        wifi_config_t wifi_conf = {
                .sta = {
                        .ssid = "fat-man",
                        .password = "091102IAUG45",
                        .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                },
        };

        esp_err_t ret = nvs_flash_init();

        if (ret == ESP_ERR_NVS_NO_FREE_PAGES
            || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

                /* Erase partition and try again. */
                ESP_ERROR_CHECK(nvs_flash_erase());
                ret = nvs_flash_init();
        }

        ESP_ERROR_CHECK(ret);

        /* Initialize the ESP32 as I2C master. */
        i2c_master_init();

        /* Initialize the ADXL345 accelerometer for I2C. */
        adxl345_init();

        /* Connect to a Wi-Fi network. */
        wifi_init();
        wifi_connect(&wifi_conf);
}
