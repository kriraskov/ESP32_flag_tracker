#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "wifi_provisioning/manager.h"
#include "wifi_provisioning/scheme_softap.h"
#include "wifi_prov.h"
#include "wifi_sta.h"

static const char *TAG = "WIFI_PROV";

static void prov_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
        switch (event_id) {
        case WIFI_PROV_START:
                ESP_LOGI(TAG, "started provisioning");
                break;
        case WIFI_PROV_CRED_RECV: {
                wifi_sta_config_t *wifi_sta_cfg =
                        (wifi_sta_config_t *) event_data;
                ESP_LOGI(TAG, "received credentials: SSID: %s",
                         (const char *) wifi_sta_cfg->ssid);
                break;
        }
        case WIFI_PROV_CRED_FAIL: {
                wifi_prov_sta_fail_reason_t *reason =
                        (wifi_prov_sta_fail_reason_t *) event_data;
                ESP_LOGE(TAG, "provisioning failed: %s",
                         esp_err_to_name(*reason));
                break;
        }
        case WIFI_PROV_CRED_SUCCESS:
                ESP_LOGI(TAG, "provisioning successful");
                break;
        case WIFI_PROV_END:
                /* De-initialize manager once provisioning is finished. */
                wifi_prov_mgr_deinit();
                break;
        default:
                break;
        }
}

static void protocomm_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{

        switch (event_id) {
                case PROTOCOMM_SECURITY_SESSION_SETUP_OK:
                        ESP_LOGI(TAG, "secured session established");
                        break;
                case PROTOCOMM_SECURITY_SESSION_INVALID_SECURITY_PARAMS:
                        ESP_LOGE(TAG, "failed to establish secure session: "
                                      "invalid security parameters");
                        break;
                case PROTOCOMM_SECURITY_SESSION_CREDENTIALS_MISMATCH:
                        ESP_LOGE(TAG, "failed to establish secure session: "
                                      "incorrect username or PoP");
                        break;
                default:
                        break;
        }
}

static void get_device_service_name(char *service_name)
{
        uint8_t eth_mac[6];

        esp_wifi_get_mac(WIFI_IF_STA, eth_mac);
        sprintf(service_name, "PROV_%02X%02X%02X", eth_mac[3], eth_mac[4],
                eth_mac[5]);
}

void wifi_prov_init() {
        wifi_prov_mgr_config_t config = {
                .scheme = wifi_prov_scheme_softap,
                .scheme_event_handler = WIFI_PROV_EVENT_HANDLER_NONE,
        };

        ESP_ERROR_CHECK(esp_event_handler_register(
                WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &prov_event_handler, NULL));
        ESP_ERROR_CHECK(esp_event_handler_register(
                PROTOCOMM_SECURITY_SESSION_EVENT, ESP_EVENT_ANY_ID,
                &protocomm_event_handler, NULL));

        esp_netif_create_default_wifi_ap();

        ESP_ERROR_CHECK(wifi_prov_mgr_init(config));
}

void wifi_prov_start(void)
{
        char service_name[12];
        const char *pop = "abcd1234";
        const char *service_key = NULL;
        wifi_prov_security1_params_t *sec_params = pop;

        ESP_LOGI(TAG, "starting provisioning");
        get_device_service_name(service_name);
        ESP_ERROR_CHECK(wifi_prov_mgr_start_provisioning(
                WIFI_PROV_SECURITY_1, (const void *) sec_params, service_name,
                service_key));
}