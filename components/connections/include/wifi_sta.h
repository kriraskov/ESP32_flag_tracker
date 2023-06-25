#ifndef ESP32_FLAG_TRACKER_WIFI_STA_H
#define ESP32_FLAG_TRACKER_WIFI_STA_H

#include <stdint.h>

/**
 * @brief Initialize basic Wi-Fi tasks.
 *
 * Initializes the TCP/IP stack (lwIP) and configures the Wi-Fi driver.
 */
void wifi_sta_init(void);

/**
 * @brief Connect to an AP.
 *
 * Sets the device in STA mode and connects to an AP according to the
 * credentials stored in NVS.
 *
 * @note Wi-Fi credentials can be retrieved either by provisioning or
 * by calling esp_wifi_set_config().
 */
void wifi_sta_connect();

#endif //ESP32_FLAG_TRACKER_WIFI_STA_H
