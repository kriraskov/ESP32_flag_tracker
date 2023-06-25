#include <esp_log.h>
#include "nvs_flash.h"
#include "wifi_provisioning/manager.h"
#include "i2c_master.h"
#include "i2c_adxl345.h"
#include "wifi_sta.h"
#include "wifi_prov.h"

static const char *TAG = "ESP32_flag_tracker";

void app_main(void)
{
        bool wifi_provisioned = false;
        bool reset_prov = true;

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
        i2c_adxl345_init();

        /* Connect to a Wi-Fi network. */
        wifi_sta_init();
        wifi_prov_init();

        if (reset_prov)
                wifi_prov_mgr_reset_provisioning();

        ESP_ERROR_CHECK(wifi_prov_mgr_is_provisioned(&wifi_provisioned));

        if (wifi_provisioned) {
                ESP_LOGI(TAG, "already provisioned: starting STA");
                wifi_prov_mgr_deinit();
                wifi_sta_connect();
        } else {
                wifi_prov_start();
        }
}
