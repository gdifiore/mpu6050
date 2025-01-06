#include <Wire.h>
#include "mpu6050.hpp"  // lib include

MPU6050 mpu;    // instance

void setup() {
    if (!mpu.MPU6050_init()) {
        Serial.println("Custom library initialization failed!");
        while (1);
    }
}

void loop() {
    //...
    MPU6050_Data sensorData;
    //...
    if (mpu.MPU6050_read(&sensorData)) {
        float customAccX = mpu.convertAccel(sensorData.acc_x);
        float customAccY = mpu.convertAccel(sensorData.acc_y);
        float customAccZ = mpu.convertAccel(sensorData.acc_z);
        float customGyroX = mpu.convertGyro(sensorData.gyro_x);
        float customGyroY = mpu.convertGyro(sensorData.gyro_y);
        float customGyroZ = mpu.convertGyro(sensorData.gyro_z);
    }
}