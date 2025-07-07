#pragma once

// Initializes the IMU (sets up I2C and wakes the MPU6050)
void imu_init();

// Reads and converts raw IMU values into real-world units
void imu_read(float* acc, float* gyro);
