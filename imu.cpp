#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "imu.hpp"

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5
#define MPU6050_ADDR 0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B

void imu_init() {
    i2c_init(I2C_PORT, 400 * 1000); // 400 kHz I2C
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    uint8_t buf[] = {PWR_MGMT_1, 0x00}; // Wake up the MPU6050
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, buf, 2, false);
}

int16_t read_word(uint8_t reg) {
    uint8_t buf[2];
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, buf, 2, false);
    return (int16_t)((buf[0] << 8) | buf[1]);
}

void imu_read(float* acc, float* gyro) {
    int16_t ax = read_word(ACCEL_XOUT_H);
    int16_t ay = read_word(ACCEL_XOUT_H + 2);
    int16_t az = read_word(ACCEL_XOUT_H + 4);
    int16_t gx = read_word(ACCEL_XOUT_H + 8);
    int16_t gy = read_word(ACCEL_XOUT_H + 10);
    int16_t gz = read_word(ACCEL_XOUT_H + 12);

    acc[0] = ax / 16384.0f;
    acc[1] = ay / 16384.0f;
    acc[2] = az / 16384.0f;

    gyro[0] = gx / 131.0f;
    gyro[1] = gy / 131.0f;
    gyro[2] = gz / 131.0f;
}
