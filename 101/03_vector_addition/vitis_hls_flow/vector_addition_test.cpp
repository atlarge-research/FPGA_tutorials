/*
    Test bench for vector addition.
*/

#include <assert.h>
#include <iostream>
#include "vector_addition.h"


void test_vector_addition(const int N) {

	std::cout << "Testing with vectors of "<< N << " elements."<<std::endl;
	// Generate input data
	int* x = new int[N];
	int* y = new int[N];
	int* z = new int[N];

    // Test vector addition
    vector_add(x, y, z, N);

    // Check result
    for (int i = 0; i < N; i++)
    	assert(z[i] == (x[i]+y[i]));
}

int main() {
	int N = 512;
	std::cout << "Insert vector size: " << std::endl;
    test_vector_addition(N);
}
