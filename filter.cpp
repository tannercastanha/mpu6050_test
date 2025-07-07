#include "filter.hpp"

float low_pass_filter(float input, float prev_output, float alpha) {
    return alpha * input + (1.0f - alpha) * prev_output;
}
