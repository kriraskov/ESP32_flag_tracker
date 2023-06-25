#include <esp_log.h>
#include "driver/i2c.h"
#include "i2c_master.h"
#include "i2c_adxl345.h"

static const char *TAG = "ADXL345";

static void adxl345_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
        ESP_ERROR_CHECK(i2c_master_write_read_device(
                I2C_MASTER_NUM, ADXL345_SENSOR_ADDR, &reg_addr, 1, data, len,
                I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS));
}

static void adxl345_register_write_byte(uint8_t reg_addr, uint8_t data)
{
        uint8_t write_buf[2] = {reg_addr, data};

        ESP_ERROR_CHECK(i2c_master_write_to_device(
                I2C_MASTER_NUM, ADXL345_SENSOR_ADDR, write_buf,
                sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS));
}

void i2c_adxl345_init(void)
{
        adxl345_register_write_byte(ADXL345_REG_BW_RATE, 0x1C);
        ESP_LOGI(TAG, "Using low power mode at 400 Hz.");

        /* Data formatting settings. */
        adxl345_register_write_byte(ADXL345_REG_DATA_FORMAT, 0x0E);
        ESP_LOGI(TAG, "Using full-resolution mode, left justified, +/-8g.");

        /* Set in standby mode and back to measurement mode. */
        adxl345_register_write_byte(ADXL345_REG_POWER_CTL, 0x00);
        adxl345_register_write_byte(ADXL345_REG_POWER_CTL, 0x08);
        ESP_LOGI(TAG, "Set to standby mode and back to measurement mode.");

        ESP_LOGI(TAG, "ADXL345 accelerometer initialized successfully.");
}

void i2c_adxl345_read_data(int16_t *ax, int16_t *ay, int16_t *az)
{
        uint8_t data[6];

        adxl345_register_read(ADXL345_REG_DATAX0, data, 6);

        *ax = (int16_t) ((int16_t) (data[1] << 8) | data[0]);
        *ay = (int16_t) ((int16_t) (data[3] << 8) | data[2]);
        *az = (int16_t) ((int16_t) (data[5] << 8) | data[4]);
}
