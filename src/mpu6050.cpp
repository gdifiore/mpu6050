/**
 * @brief mpu6050.cpp
 * @author Gabriel DiFiore
 * @date 2024-12-27
 *
 * Implementation of a driver for the MPU-6050 Six-Axis (Accelerometer + Gyro) Sensor.
 */

#include "mpu6050.hpp"
#include <Wire.h>

MPU6050::MPU6050(uint8_t address, GyroRange gRange, AccelRange aRange) :
    i2cAddress(address),
    gyroRange(gRange),
    accelRange(aRange) {
}
/*
 * Initialize MPU6050 with default settings.
 * Returns true if successful, false otherwise.
 */
bool MPU6050::MPU6050_init() {    // Wake up the MPU6050
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_PWR_MGMT_1_REGISTER);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    // Set sample rate to 1kHz
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_SMPLRT_DIV_REGISTER);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    // Set the Digital Low Pass Filter to 0 (no filtering)
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_CONFIG_REGISTER);
    Wire.write(0x00);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    // Configure gyroscope range
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_GYRO_CONFIG_REGISTER);
    Wire.write(gyroRange);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    // Configure accelerometer range
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_ACCEL_CONFIG_REGISTER);
    Wire.write(accelRange);
    if (Wire.endTransmission() != 0) {
        return false;
    }

    return true;
}

/**
 * Read raw acceleration and gyroscope data from MPU6050.
 * Returns true if successful, false otherwise.
 */
bool MPU6050::MPU6050_read(MPU6050_Data *data) {
    if (!data) return false;

    uint8_t buffer[14];

    // Read 14 bytes from the MPU6050 starting at the ACCEL_OUT_REGISTER
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(MPU6050_ACCEL_OUT_REGISTER);
    if (Wire.endTransmission(false) != 0) {
        return false;
    }

    // Request 14 bytes from the MPU6050
    Wire.requestFrom(MPU6050_ADDR, 14);
    if (Wire.available() != 14) {
        return false;
    }

    // Store the received data into the buffer
    for (uint8_t i = 0; i < 14; i++) {
        buffer[i] = Wire.read();
    }

    // Combine high and low bytes for each measurement
    data->acc_x = (buffer[0] << 8) | buffer[1];
    data->acc_y = (buffer[2] << 8) | buffer[3];
    data->acc_z = (buffer[4] << 8) | buffer[5];
    data->gyro_x = (buffer[8] << 8) | buffer[9];
    data->gyro_y = (buffer[10] << 8) | buffer[11];
    data->gyro_z = (buffer[12] << 8) | buffer[13];

    return true;
}

float MPU6050::convertAccel(int16_t rawValue) {
    float sensitivity;
    switch (accelRange) {
        case ACCEL_RANGE_2G:  sensitivity = 16384.0; break;
        case ACCEL_RANGE_4G:  sensitivity = 8192.0; break;
        case ACCEL_RANGE_8G:  sensitivity = 4096.0; break;
        case ACCEL_RANGE_16G: sensitivity = 2048.0; break;
        default:              sensitivity = 16384.0; break; // Default to ±2g
    }
    return rawValue / sensitivity;
}

float MPU6050::convertGyro(int16_t rawValue) {
    float sensitivity;
    switch (gyroRange) {
        case GYRO_RANGE_250DPS:  sensitivity = 131.0; break;
        case GYRO_RANGE_500DPS:  sensitivity = 65.5; break;
        case GYRO_RANGE_1000DPS: sensitivity = 32.8; break;
        case GYRO_RANGE_2000DPS: sensitivity = 16.4; break;
        default:                 sensitivity = 131.0; break; // Default to ±250°/s
    }
    return rawValue / sensitivity;
}
