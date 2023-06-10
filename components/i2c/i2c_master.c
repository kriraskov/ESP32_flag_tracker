/* I2C Master setup.
 *
 * Includes
 */
#include <esp_check.h>
#include "driver/i2c.h"
#include "i2c_master.h"

static const char *TAG = "I2C_MASTER";
/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void)
{
        esp_err_t ret = ESP_OK;

        /* Configure GPIO for I2C. */
         i2c_config_t conf = {
                .mode = I2C_MODE_MASTER,
                .sda_io_num = I2C_MASTER_SDA_IO,
                .scl_io_num = I2C_MASTER_SCL_IO,
                .sda_pullup_en = GPIO_PULLUP_ENABLE,
                .scl_pullup_en = GPIO_PULLUP_ENABLE,
                .master.clk_speed = I2C_MASTER_FREQ_HZ,
        };

        ESP_GOTO_ON_ERROR(i2c_param_config(I2C_MASTER_NUM, &conf), err, TAG,
                          "Failed to configure GPIO.");

        ESP_GOTO_ON_ERROR(i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                                             I2C_MASTER_RX_BUF_DISABLE,
                                             I2C_MASTER_TX_BUF_DISABLE, 0),
                          err, TAG, "Failed to install i2c driver.");

err:
        return ret;
}
