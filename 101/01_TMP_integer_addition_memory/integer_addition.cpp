// Function implementations
#include "integer_addition.h"

// #include "data.h"
#define N 1000

int int_add(int a, int b) {
    // Sum the two numbers
    return a + b;
}

int int_add_array(int start, int data[N]) {
    // Accumulates the values in the array
    int result = start;

add_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS unroll factor = 5
        result += data[i];
    }
    return result;
}