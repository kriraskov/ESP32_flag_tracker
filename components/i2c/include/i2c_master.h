#ifndef ESP32_FLAG_TRACKER_I2C_MASTER_H
#define ESP32_FLAG_TRACKER_I2C_MASTER_H

/** I2C master i2c port number. */
#define I2C_MASTER_NUM              0

/** Maximum time to wait before issuing a timeout. */
#define I2C_MASTER_TIMEOUT_MS       1000

/**
 * @brief i2c master initialization
 */
void i2c_master_init(void);

#endif //ESP32_FLAG_TRACKER_I2C_MASTER_H
