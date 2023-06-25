#include <esp_log.h>
#include "driver/i2c.h"
#include "i2c_master.h"

static const char *TAG = "I2C_MASTER";

/** GPIO number used for I2C master clock. */
#define I2C_MASTER_SCL_IO           3

/** GPIO number used for I2C master data. */
#define I2C_MASTER_SDA_IO           2

/** I2C master clock frequency. */
#define I2C_MASTER_FREQ_HZ          400000

/** I2C master doesn't need buffer. */
#define I2C_MASTER_TX_BUF_DISABLE   0

/** I2C master doesn't need buffer. */
#define I2C_MASTER_RX_BUF_DISABLE   0

void i2c_master_init(void)
{
        /* Configure GPIO for I2C. */
         i2c_config_t conf = {
                .mode = I2C_MODE_MASTER,
                .sda_io_num = I2C_MASTER_SDA_IO,
                .scl_io_num = I2C_MASTER_SCL_IO,
                .sda_pullup_en = GPIO_PULLUP_ENABLE,
                .scl_pullup_en = GPIO_PULLUP_ENABLE,
                .master.clk_speed = I2C_MASTER_FREQ_HZ,
        };

        ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
        ESP_LOGI(TAG, "Successfully configured GPIO.");

        ESP_ERROR_CHECK(i2c_driver_install(
                I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE,
                I2C_MASTER_TX_BUF_DISABLE, 0));
        ESP_LOGI(TAG, "Successfully installed driver.");

        ESP_LOGI(TAG, "I2C initialized successfully.");
}
