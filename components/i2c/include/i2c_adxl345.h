#ifndef ESP32_FLAG_TRACKER_I2C_ADXL345_H
#define ESP32_FLAG_TRACKER_I2C_ADXL345_H

#include <stdint.h>
#include <stddef.h>

/** Slave address of the ADXL345 sensor. */
#define ADXL345_SENSOR_ADDR                 0x53

/** Data rate and power control register */
#define ADXL345_REG_BW_RATE                 0x2C

/** Power control register. */
#define ADXL345_REG_POWER_CTL               0x2D

/** Data format control register. */
#define ADXL345_REG_DATA_FORMAT             0x31

/** X-Axis data 0 register. */
#define ADXL345_REG_DATAX0                  0x32

/**
 * @brief ADXL345 initialization.
 */
void i2c_adxl345_init(void);

/**
 * @brief Read raw acceleration data from the ADXL345 sensor. Divide the
 * values by 0x0FFF to get the acceleration as multiples of 1g.
 *
 * @param ax Pointer to x-axis acceleration data.
 * @param ay Pointer to y-axis acceleration data.
 * @param az Pointer to z-axis acceleration data.
 */
void i2c_adxl345_read_data(int16_t *ax, int16_t *ay, int16_t *az);

#endif //ESP32_FLAG_TRACKER_I2C_ADXL345_H
