#include "adxl345.h"

void app_main(void)
{
    uint8_t data[2];
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");

    /*
     * Read the ADXL345 WHO_AM_I register, on power up the register
     * should have the value 0x71
     */
    ESP_ERROR_CHECK(adxl345_register_read(ADXL345_WHO_AM_I_REG_ADDR, data, 1));
    ESP_LOGI(TAG, "WHO_AM_I = %X", data[0]);

    /* Demonstrate writing by resetting the ADXL345 */
    ESP_ERROR_CHECK(adxl345_register_write_byte(ADXL345_PWR_MGMT_1_REG_ADDR,
                                                1 << ADXL345_RESET_BIT));

    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C de-initialized successfully");
}
