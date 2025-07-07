#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "imu.hpp"
#include "filter.hpp"

#define BUTTON_PIN 15

int main() 
{
    stdio_init_all();
    imu_init();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Raw data mode from MPU6050 for faster data but more noise
    float acc[3] = {0};
    float gyro[3] = {0};
    // Filtered data mode from MPU6050 for slower data but less noise
    float acc_f[3] = {0};
    float gyro_f[3] = {0};
    // Low alpha for heavy smoothing with low-pass filter
    float alpha = 0.1f;

    bool use_filtered = false;
    bool last_button = false;

    while (true)
    {
        imu_read(acc, gyro);

        // start output mode in raw
        // when button is pressed, data output mode switches to either raw or filtered
        bool current_button = !gpio_get(BUTTON_PIN);
        if (current_button && !last_button) {
            use_filtered = !use_filtered;
            printf("Mode: %s\n", use_filtered ? "FILTERED" : "RAW");
        }
        last_button = current_button;

        for (int i = 0; i < 3; i++) {
            acc_f[i] = low_pass_filter(acc[i], acc_f[i], alpha);
            gyro_f[i] = low_pass_filter(gyro[i], gyro_f[i], alpha);
        }

        float* a = use_filtered ? acc_f : acc;
        float* g = use_filtered ? gyro_f : gyro;

        printf("%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            use_filtered ? "FILTERED" : "RAW",
            a[0], a[1], a[2],
            g[0], g[1], g[2]
        );

        sleep_ms(100);
    }

    return 0;
}
