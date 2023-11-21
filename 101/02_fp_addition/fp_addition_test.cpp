/*
    Test bench for integer addition.
    NOTE: you have to properly comment out testing functions in main according
    to the evaluated function
*/

#include "fp_addition.h"

#include <assert.h>
#include <stdio.h>

#include <cmath>

#include "data.h"

void test_fp_add_a_b(FP_TYPE a, FP_TYPE b) {
    // Test addition with two floating point numbers

    FP_TYPE res = fp_add(a, b);
    printf("Result of %.3f + %.3f = %.3f\n", a, b, res);

    assert(fabs(res - (a + b) < 1e-6));
}

void test_fp_add_array(FP_TYPE start) {
    // Test accumulation over an array

    FP_TYPE res = fp_add_array(start);
    printf("Result: %.3f\n", res);

    FP_TYPE exp_result = start;
    for (int i = 0; i < N; i++)
        exp_result += data[i];
    printf("Expected result: %.3f\n", exp_result);
    assert(fabs(res - exp_result) < 1e-6);
}

int main() {
    // Test two numbers addition
    test_fp_add_a_b(1.1, 1.2);

    // Test array addition
    // test_fp_add_array(0);
}