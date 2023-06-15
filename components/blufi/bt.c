#include "esp_bt.h"
#include "bt.h"

void blufi_init(void)
{
        esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
        ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));
}

void blufi_deinit(void)
{
        ESP_ERROR_CHECK(esp_bt_controller_disable());
        ESP_ERROR_CHECK(esp_bt_controller_deinit());
}