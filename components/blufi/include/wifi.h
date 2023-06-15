#ifndef ESP32_FLAG_ACCEL_WIFI_H
#define ESP32_FLAG_ACCEL_WIFI_H

#include <stdint.h>

/** @brief Initialize basic Wi-Fi tasks. */
void wifi_init(void);

/**
 * @brief Set up a Wi-Fi connection.
 *
 * @param conf Wi-Fi configuration to apply.
 */
void wifi_connect(wifi_config_t *conf);

#endif //ESP32_FLAG_ACCEL_WIFI_H
