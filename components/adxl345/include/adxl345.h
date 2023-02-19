#ifndef ESP32_FLAG_ACCEL_ACCELEROMETER_H
#define ESP32_FLAG_ACCEL_ACCELEROMETER_H

#define ADXL345_SENSOR_ADDR                 0x53        /*!< Slave address of the ADXL345 sensor */

#define ADXL345_REG_THRESH_ACT              0x24
#define ADXL345_REG_THRESH_INACT            0x25
#define ADXL345_REG_TIME_INACT              0x26
#define ADXL345_REG_BW_RATE                 0x2C        /*!< Register address of the data rate and power mode control register */
#define ADXL345_REG_POWER_CTL               0x2D
#define ADXL345_REG_INT_ENABLE              0x2E
#define ADXL345_REG_INT_MAP                 0x2F
#define ADXL345_REG_DATA_FORMAT             0x31        /*!< Register address of the data format control register */
#define ADXL345_REG_DATAX0                  0x32

#define ADXL345_RESET_BIT                   7
esp_err_t adxl345_register_read(uint8_t reg_addr, uint8_t *data, size_t len);

esp_err_t adxl345_register_write_byte(uint8_t reg_addr, uint8_t data);

esp_err_t adxl345_i2c_slave_init(void);

esp_err_t adxl345_read_data(int16_t *ax, int16_t *ay, int16_t *az);

#endif //ESP32_FLAG_ACCEL_ACCELEROMETER_H
