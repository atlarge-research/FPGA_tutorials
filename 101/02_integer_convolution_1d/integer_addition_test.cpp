/*
    Test bench for integer addition.
    NOTE: you have to properly comment out testing functions in main according
    to the evaluated function
*/
#include "integer_addition.h"

#include <assert.h>
#include <stdio.h>

//#include "data.h"

#define N 1000

// TODO: CREATE EXAMPLE WITH BRAM CONTENTION (STENCIL 1D)

void test_int_add_array(int in[N]) {
    // Test array accumulation

	int* out_fpga = new int[N];
    int_add_array(in ,out_fpga);

    int* exp_result = new int[N];
	for (int i = 2; i < N; i++) {
		exp_result[i] = (in[i] + in[i-1] + in[i-2])/3;
	}


	for (int i = 2; i < N; i++)
		assert(out_fpga[i] == exp_result[i]);

	printf("Success\n");
}

int main() {
    // TODO: handle data: if static it can be easily replicated (it is read only)
    
     int* array = new int[N]();
     for (int i=0; i<N; i++)
    	 array[i] = i+1;
    test_int_add_array(array);
}
