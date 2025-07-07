#pragma once

// Applies a first-order low-pass filter to smooth noise
float low_pass_filter(float input, float prev_output, float alpha);
