// Function implementations
#include "vector_addition.h"

//#define N 1000

void vector_add(int* x, int* y, int *z, const int N) {
    // Sum the two vectors
	add_loop: for (int i = 0; i < N; i++) {
		#pragma HLS unroll factor=4
		z[i] = x[i] + y[i] ;
	}

}
