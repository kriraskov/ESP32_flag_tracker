#include <esp_log.h>
#include "esp_wifi.h"
#include "esp_bt.h"
#include "freertos/event_groups.h"
#include "wifi_sta.h"

static const char *TAG = "WIFI";

/** Maximum number of connection attempts to AP. */
#define WIFI_MAXIMUM_RETRY      5

/** Status bit indicating successfull connection attempt. */
#define WIFI_CONNECTED_BIT      BIT0

/** Status bit indicating failed connection attempt. */
#define WIFI_FAIL_BIT           BIT1

/** Number of connection attempts to AP. */
static int n_retries = 0;

/** Event group handle for Wi-Fi events. */
static EventGroupHandle_t s_wifi_event_group;

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
        switch (event_id) {
        case WIFI_EVENT_STA_START:
                esp_wifi_connect();
                break;
        case WIFI_EVENT_STA_DISCONNECTED: {
                wifi_event_sta_disconnected_t *disconnected =
                        (wifi_event_sta_disconnected_t *) event_data;

                if (disconnected->reason == WIFI_REASON_ASSOC_LEAVE) {
                        ESP_LOGI(TAG, "disconnected");
                        n_retries = 0;
                } else if (n_retries < WIFI_MAXIMUM_RETRY) {
                        ESP_LOGI(TAG, "disconnected: reconnecting...");
                        esp_wifi_connect();
                        n_retries++;
                } else {
                        ESP_LOGE(TAG,"connection failed: %s",
                                 esp_err_to_name(disconnected->reason));
                        xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
                }

                break;
        }
        default:
                break;
        }
}

static void ip_event_handler(void* arg, esp_event_base_t event_base,
                             int32_t event_id, void* event_data)
{
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        n_retries = 0;

        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
}

void wifi_sta_init(void)
{
        s_wifi_event_group = xEventGroupCreate();
        wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();

        ESP_ERROR_CHECK(esp_netif_init());                      // TCP/IP stack
        ESP_ERROR_CHECK(esp_event_loop_create_default());       // FreeRTOS

        esp_netif_create_default_wifi_sta();

        ESP_ERROR_CHECK(esp_wifi_init(&config));

        /* Register the event handlers. */
        ESP_ERROR_CHECK(esp_event_handler_register(
                WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
        ESP_ERROR_CHECK(esp_event_handler_register(
                IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL));

        ESP_LOGI(TAG, "initialized driver");
}

void wifi_sta_connect(void)
{
        /* Set to STA before connecting; might be in AP mode from other tasks */
        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_start());

        /* Wait until connection established or failed, then read
         * status bits (set by event_handler()). */
        EventBits_t bits = xEventGroupWaitBits(
                s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                pdTRUE, pdFALSE, portMAX_DELAY);

        if (bits & WIFI_CONNECTED_BIT)
                ESP_LOGI(TAG, "connected");
        else if (bits & WIFI_FAIL_BIT)
                ESP_LOGE(TAG, "connection failed");
        else
                ESP_LOGE(TAG, "unexpected event");
}