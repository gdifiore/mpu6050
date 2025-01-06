// MPU-6050 Register Map & Descriptions
// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>

#define MPU6050_ADDR 0x68
#define MPU6050_PWR_MGMT_1_REGISTER 0x6B
#define MPU6050_SMPLRT_DIV_REGISTER 0x19
#define MPU6050_CONFIG_REGISTER 0x1A
#define MPU6050_GYRO_CONFIG_REGISTER 0x1B
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1C
#define MPU6050_ACCEL_OUT_REGISTER 0x3B
#define MPU6050_GYRO_OUT_REGISTER 0x43

typedef enum {
    GYRO_RANGE_250DPS = 0x00,  // ±250°/s
    GYRO_RANGE_500DPS = 0x08,  // ±500°/s
    GYRO_RANGE_1000DPS = 0x10, // ±1000°/s
    GYRO_RANGE_2000DPS = 0x18  // ±2000°/s
} GyroRange;

typedef enum {
    ACCEL_RANGE_2G = 0x00,  // ±2g
    ACCEL_RANGE_4G = 0x08,  // ±4g
    ACCEL_RANGE_8G = 0x10,  // ±8g
    ACCEL_RANGE_16G = 0x18  // ±16g
} AccelRange;

typedef struct {
    int16_t acc_x, acc_y, acc_z;
    int16_t gyro_x, gyro_y, gyro_z;
} MPU6050_Data;

class MPU6050 {
private:
    uint8_t i2cAddress;
    GyroRange gyroRange;
    AccelRange accelRange;

public:
    // Constructor
    MPU6050(uint8_t address = MPU6050_ADDR, GyroRange gyro = GYRO_RANGE_250DPS, AccelRange accel = ACCEL_RANGE_2G);

    bool MPU6050_init();
    bool MPU6050_read(MPU6050_Data* data);
    float convertAccel(int16_t rawValue);
    float convertGyro(int16_t rawValue);
};

#endif // MPU6050_H
