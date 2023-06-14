#ifndef ESP32_FLAG_ACCEL_WIFI_H
#define ESP32_FLAG_ACCEL_WIFI_H

#include <stdint.h>

/**
 * @brief Initialize the NVS flash partition for Wi-Fi.
 *
 * @note If the underlying API returns ESP_ERR_NVS_NO_FREE_PAGES or
 * ESP_ERR_NVS_NEW_VERSION_FOUND error codes, the NVS partition is
 * erased and re-initialized.
 */
void wifi_nvs_flash_init(void);

/** @brief Initialize basic Wi-Fi tasks. */
void wifi_init(void);

/**
 * @brief Register event handler instance.
 *
 * Register event_handler to the event loop for the WIFI_EVENT and
 * IP_EVENT identifiers.
 */
void wifi_event_handler_instance_register(void);

/**
 * @brief Configure the Wi-Fi driver.
 *
 * @param conf Wi-Fi configuration to apply.
 */
void wifi_config(wifi_config_t *conf);

/**
 * @brief Set up a Wi-Fi connection.
 *
 * Configure and starts the Wi-Fi driver and connect to a network.
 *
 * @param conf Wi-Fi configuration to apply.
 */
void wifi_connect(wifi_config_t *conf);

#endif //ESP32_FLAG_ACCEL_WIFI_H
