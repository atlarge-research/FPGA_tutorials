/*
    Test bench for integer addition.
    NOTE: you have to properly comment out testing functions in main according
    to the evaluated function
*/
#include "integer_addition.h"

#include <assert.h>
#include <stdio.h>

#include "data.h"

void test_int_add_a_b(int a, int b) {
    // Test simple addition
    int res = int_add(a, b);
    printf("Result of %d + %d = %d\n", a, b, res);
    assert(res == a + b);
}

void test_int_add_array(int start) {
    // Test array accumulation
    int res = int_add_array(start);
    printf("Result: %d\n", res);

    int exp_result = start;
    for (int i = 0; i < 1000; i++)
        exp_result += data[i];
    printf("Expected result: %d\n", exp_result);
    assert(res == exp_result);
}

int main() {
    // Test two numbers addition
//     test_int_add_a_b(10, 12);

    // Test array accumulation, starting from 10
    test_int_add_array(10);
}
