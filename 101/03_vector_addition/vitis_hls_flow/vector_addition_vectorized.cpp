// Function implementations
#include "vector_addition_vectorized.h"

//#define N 1000

void vector_add(t_int8Vec* x, t_int8Vec* y, t_int8Vec *z, const int N) {
    // Sum the two vectors
	add_loop: for (int i = 0; i < N/8; i++) {
		z[i] = x[i] + y[i] ;
	}

}
