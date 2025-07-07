# mpu6050_test
Generates .uf2 file to read and output raw and filtered data using a MPU6050 IMU  and Raspberry Pi Pico W

filter.hpp and filter.cpp contain the low-pass filter function to smooth data
imu.hpp and imu.cpp contains the functions to initialize the imu and read data from sensors
main.cpp is used to wake up imu, read data, and outputs data either in raw or filtered form
