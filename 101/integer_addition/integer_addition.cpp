// Function implementation
#include "integer_addition.h"

#include "data.h"

int int_add(int a, int b) {
    // Sum the two numbers
    return a + b;
}

int int_add_array(int start) {
    // Accumulates the values in the array
    // NOTE: change unrolling factor to affect speed/resource utilization
    int result = start;

add_loop:
    for (int i = 0; i < 1000; i++) {
#pragma HLS UNROLL factor = 5
        result += data[i];
    }
    return result;
}