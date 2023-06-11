#include <esp_check.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include "wifi.h"

static const char *TAG = "WIFI";

/**
 * @brief Initialize Wi-Fi and connect to an access point.
 */
esp_err_t wifi_connect(const uint8_t *ssid, const uint8_t *password)
{
        esp_err_t ret = ESP_OK;

        wifi_init_config_t conf = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t wifi_config = {
                .sta = {
                        .ssid = {*ssid},
                        .password = {*password},
                },
        };

        ESP_GOTO_ON_ERROR(esp_wifi_init(&conf), err, TAG,
                          "Failed to initialize default Wi-Fi configuration.");

        ESP_GOTO_ON_ERROR(esp_wifi_set_mode(WIFI_MODE_STA), err, TAG,
                          "Failed to set Wi-Fi operating mode to station.");

        ESP_GOTO_ON_ERROR(esp_wifi_set_config(WIFI_IF_STA, &wifi_config),
                          err, TAG, "Failed to set Wi-Fi configuration");

        ESP_GOTO_ON_ERROR(esp_wifi_start(), err, TAG,
                          "Failed to start Wi-Fi.");

err:
        return ret;
}
