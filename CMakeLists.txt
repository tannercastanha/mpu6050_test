cmake_minimum_required(VERSION 3.13)

# Disable PICOTOOL
set(PICO_NO_PICOTOOL 1)


# Include Pico SDK toolchain BEFORE project()
include(pico_sdk_import.cmake)

# Define project AFTER including the SDK import
project(mpu6050_test C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Define the executable and sources
add_executable(mpu6050_test
    src/main.cpp
    src/imu.cpp
    src/filter.cpp
)

# Add the include directory for header files
target_include_directories(mpu6050_test PRIVATE include)

# Link against Pico SDK and hardware APIs
target_link_libraries(mpu6050_test
    pico_stdlib
    hardware_i2c
    hardware_uart
    hardware_pwm
    hardware_gpio
)

# Enable USB output and disable UART (you can change later if needed)
pico_enable_stdio_usb(mpu6050_test 1)
pico_enable_stdio_uart(mpu6050_test 0)

# Generate .uf2, .bin, .hex files
pico_add_extra_outputs(mpu6050_test)
