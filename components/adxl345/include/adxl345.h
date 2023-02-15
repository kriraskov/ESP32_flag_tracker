
#ifndef ESP32_FLAG_ACCEL_ACCELEROMETER_H
#define ESP32_FLAG_ACCEL_ACCELEROMETER_H

#endif //ESP32_FLAG_ACCEL_ACCELEROMETER_H

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           3         /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           2         /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0         /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000    /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0         /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0         /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define ADXL345_SENSOR_ADDR                 0x68        /*!< Slave address of the ADXL345 sensor */
#define ADXL345_WHO_AM_I_REG_ADDR           0x75        /*!< Register addresses of the "who am I" register */

#define ADXL345_PWR_MGMT_1_REG_ADDR         0x6B        /*!< Register addresses of the power managment register */
#define ADXL345_RESET_BIT                   7

esp_err_t adxl345_register_read(uint8_t reg_addr, uint8_t *data,
                                       size_t len);

esp_err_t adxl345_register_write_byte(uint8_t reg_addr, uint8_t data);

esp_err_t i2c_master_init(void);
