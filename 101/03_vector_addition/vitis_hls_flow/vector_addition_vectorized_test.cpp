/*
    Test bench for vector addition.
*/

#include <assert.h>
#include <iostream>
#include "vector_addition_vectorized.h"


void test_vector_addition(const int N) {

	std::cout << "Testing with vectors of "<< N << " elements."<<std::endl;
	// Generate input data
	int* x = new int[N];
	int* y = new int[N];
	int* z = new int[N];

    for(int i=0; i<N; i++){
		x[i] = i;
		y[i] = i-1;
	}


    

    // Test vector addition
    vector_add((t_int8Vec*)x, (t_int8Vec*)y, (t_int8Vec*)z, N);

    // Check result
    for (int i = 0; i < N; i++)
    {
        if (z[i] != (x[i]+y[i]))
            std::cout << i << ": " << z[i] << " != " <<  x[i]+y[i]<<std::endl;
    	assert(z[i] == (x[i]+y[i]));
    }
}

int main() {
	int N = 512;
	std::cout << "Insert vector size: " << std::endl;
    test_vector_addition(N);
}
