// MPU-6050 Register Map & Descriptions
// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define MPU6050_ADDR 0x68
#define MPU6050_PWR_MGMT_1_REGISTER 0x6B
#define MPU6050_SMPLRT_DIV_REGISTER 0x19
#define MPU6050_CONFIG_REGISTER 0x1A
#define MPU6050_GYRO_CONFIG_REGISTER 0x1B
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1C
#define MPU6050_ACCEL_OUT_REGISTER    0x3B
#define MPU6050_GYRO_OUT_REGISTER 0x43

// Data structure to hold the sensor readings
typedef struct {
    int16_t acc_x, acc_y, acc_z;
    int16_t gyro_x, gyro_y, gyro_z;
} MPU6050_Data;
