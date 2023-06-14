#ifndef ESP32_FLAG_ACCEL_ADXL345_H
#define ESP32_FLAG_ACCEL_ADXL345_H

#define ADXL345_SENSOR_ADDR                 0x53        /*!< Slave address of the ADXL345 sensor. */

#define ADXL345_REG_BW_RATE                 0x2C        /*!< Data rate and power control register */
#define ADXL345_REG_POWER_CTL               0x2D        /*!< Power control register. */
#define ADXL345_REG_DATA_FORMAT             0x31        /*!< Data format control register. */
#define ADXL345_REG_DATAX0                  0x32        /*!< X-Axis data 0 register. */

/**
 * @brief Read a sequence of bytes from an ADXL345 sensor registers.
 */
void adxl345_register_read(uint8_t reg_addr, uint8_t *data, size_t len);

/**
 * @brief Write a byte to an ADXL345 sensor register.
 */
void adxl345_register_write_byte(uint8_t reg_addr, uint8_t data);

/**
 * @brief ADXL345 initialization.
 */
void adxl345_init(void);

/**
 * @brief Read raw acceleration data from the ADXL345 sensor. Divide the
 * values by 0x0FFF to get the acceleration as multiples of 1g.
 *
 * @param ax Pointer to x-axis acceleration data.
 * @param ay Pointer to y-axis acceleration data.
 * @param az Pointer to z-axis acceleration data.
 */
void adxl345_read_data(int16_t *ax, int16_t *ay, int16_t *az);

#endif //ESP32_FLAG_ACCEL_ADXL345_H
