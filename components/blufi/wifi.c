#include <esp_log.h>
#include <esp_wifi.h>
#include "freertos/event_groups.h"
#include "esp_blufi_api.h"
#include "wifi.h"

static const char *TAG = "WIFI";

/** Maximum number of connection attempts to AP. */
#define WIFI_MAXIMUM_RETRY      5

/** Status bit indicating successfull connection attempt. */
#define WIFI_CONNECTED_BIT      BIT0

/** Status bit indicating failed connection attempt. */
#define WIFI_FAIL_BIT           BIT1

/** Number of connection attempts to AP. */
static int s_retry_num = 0;

/** Event group handle for Wi-Fi events. */
static EventGroupHandle_t s_wifi_event_group;

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
        switch (event_id) {
        case WIFI_EVENT_STA_START:
                esp_wifi_connect();
                break;
        case WIFI_EVENT_STA_DISCONNECTED:
                if (s_retry_num < WIFI_MAXIMUM_RETRY) {
                        esp_wifi_connect();
                        ESP_LOGI(TAG, "retry to connect to the AP");
                        s_retry_num++;
                } else {
                        xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
                        ESP_LOGI(TAG,"connect to the AP fail");
                }
                break;
        default:
                break;
        }
}

static void ip_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;

        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        s_retry_num = 0;

        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));

}

void wifi_init(void)
{
        s_wifi_event_group = xEventGroupCreate();
        wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();

        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());

        esp_netif_create_default_wifi_sta();

        ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));

        /* Register the event handlers. */
        ESP_ERROR_CHECK(esp_event_handler_register(
                WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
        ESP_ERROR_CHECK(esp_event_handler_register(
                IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL));

        /* Configure and start the Wi-Fi driver. */
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_LOGI(TAG, "initialized driver");
}

void wifi_connect(wifi_config_t *conf)
{
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, conf));
        ESP_ERROR_CHECK(esp_wifi_start());

        /* Wait until connection established or failed, then read
         * status bits (set by event_handler()). */
        EventBits_t bits = xEventGroupWaitBits(
                s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                pdFALSE, pdFALSE, portMAX_DELAY);

        /* xEventGroupWaitBits() returns the bits before the call
         * returned, hence we can test which event actually happened. */
        if (bits & WIFI_CONNECTED_BIT)
                ESP_LOGI(TAG, "connected to AP: SSID: %s", conf->sta.ssid);
        else if (bits & WIFI_FAIL_BIT)
                ESP_LOGI(TAG, "connection failed: SSID: %s", conf->sta.ssid);
        else
                ESP_LOGE(TAG, "UNEXPECTED EVENT");
}
