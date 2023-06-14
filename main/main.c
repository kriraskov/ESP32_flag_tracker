#include <esp_wifi.h>
#include <esp_log.h>
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

        /* Initialize the ESP32 as I2C master. */
        i2c_master_init();

        /* Initialize the ADXL345 accelerometer for I2C. */
        adxl345_init();

        /* Connect to a Wi-Fi network. */
        wifi_connect(&wifi_conf);
}
