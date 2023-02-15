/* i2c - Simple example
 *
 * Simple I2C example that shows how to initialize I2C
 * as well as reading and writing from and to registers for a sensor connected
 * over I2C.
 *
 * The sensor used in this example is a ADXL345 inertial measurement unit.
 *
 * For other examples please check:
 * https://github.com/espressif/esp-idf/tree/master/examples
 *
 * See README.md file to get detailed usage of this example.
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
*/
#include "adxl345.h"

/**
 * @brief Read a sequence of bytes from an ADXL345 sensor registers
 */
esp_err_t adxl345_register_read(uint8_t reg_addr, uint8_t *data,
                                       size_t len)
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
        int ret;
        uint8_t write_buf[2] = {reg_addr, data};

        ret = i2c_master_write_to_device(I2C_MASTER_NUM, ADXL345_SENSOR_ADDR,
                                         write_buf, sizeof(write_buf),
                                         I2C_MASTER_TIMEOUT_MS
                                         / portTICK_PERIOD_MS);

        return ret;
}

/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void)
{
        int i2c_master_port = I2C_MASTER_NUM;

        i2c_config_t conf = {
                .mode = I2C_MODE_MASTER,
                .sda_io_num = I2C_MASTER_SDA_IO,
                .scl_io_num = I2C_MASTER_SCL_IO,
                .sda_pullup_en = GPIO_PULLUP_ENABLE,
                .scl_pullup_en = GPIO_PULLUP_ENABLE,
                .master.clk_speed = I2C_MASTER_FREQ_HZ,
        };

        i2c_param_config(i2c_master_port, &conf);

        return i2c_driver_install(i2c_master_port, conf.mode,
                                  I2C_MASTER_RX_BUF_DISABLE,
                                  I2C_MASTER_TX_BUF_DISABLE, 0);
}


