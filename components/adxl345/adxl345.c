/* ADXL345 accelerometer library.
 *
 * Includes functions to communicate with the ADXL345 accelerometer over I2C.
 */
#include <esp_check.h>
#include <esp_log.h>
#include "driver/i2c.h"
#include "i2c_master.h"
#include "adxl345.h"

static const char *TAG = "ADXL345";

/**
 * @brief Read a sequence of bytes from an ADXL345 sensor registers
 */
esp_err_t adxl345_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
        return i2c_master_write_read_device(I2C_MASTER_NUM, ADXL345_SENSOR_ADDR,
                                            &reg_addr, 1, data, len,
                                            I2C_MASTER_TIMEOUT_MS
                                            / portTICK_PERIOD_MS);
}

/**
 * @brief Write a byte to an ADXL345 sensor register
 */
esp_err_t adxl345_register_write_byte(uint8_t reg_addr, uint8_t data)
{
        uint8_t write_buf[2] = {reg_addr, data};

        return i2c_master_write_to_device(I2C_MASTER_NUM, ADXL345_SENSOR_ADDR,
                                          write_buf, sizeof(write_buf),
                                          I2C_MASTER_TIMEOUT_MS
                                          / portTICK_PERIOD_MS);
}

/**
 * @brief ADXL345 I2C slave initialization
 */
esp_err_t adxl345_i2c_slave_init(void)
{
        esp_err_t ret = ESP_OK;

        /* Use low power mode at 400 Hz. */
        ESP_GOTO_ON_ERROR(adxl345_register_write_byte(
                ADXL345_REG_BW_RATE, 0x1C), err, TAG,
                          "Failed to set power mode.");

        /* Data formatting settings. */
        ESP_GOTO_ON_ERROR(adxl345_register_write_byte(
                ADXL345_REG_DATA_FORMAT, 0x0E), err, TAG,
                          "Failed to set data formatting settings.");

        /* Set in standby mode and back to measurement mode. */
        ESP_GOTO_ON_ERROR(adxl345_register_write_byte(
                ADXL345_REG_POWER_CTL, 0x00), err, TAG,
                          "Failed to set the part in standby mode.");
        ESP_GOTO_ON_ERROR(adxl345_register_write_byte(
                ADXL345_REG_POWER_CTL, 0x08), err, TAG,
                          "Failed to set the part in measurement mode.");

err:
        return ret;
}

esp_err_t adxl345_read_data(int16_t *ax, int16_t *ay, int16_t *az)
{
        esp_err_t ret = ESP_OK;
        uint8_t data[6];

        ESP_GOTO_ON_ERROR(adxl345_register_read(
                ADXL345_REG_DATAX0, data, 6), err, TAG,
                          "Failed to read acceleration data.");

        *ax = (int16_t) ((int16_t) (data[1] << 8) | data[0]);
        *ay = (int16_t) ((int16_t) (data[3] << 8) | data[2]);
        *az = (int16_t) ((int16_t) (data[5] << 8) | data[4]);

err:
        return ret;
}
