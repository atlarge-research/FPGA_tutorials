// Function implementations

#include "fp_addition.h"

#include "data.h"

FP_TYPE fp_add(FP_TYPE a, FP_TYPE b) {
    // Sum the two numbers
    return a + b;
}

FP_TYPE fp_add_array(FP_TYPE start) {
    FP_TYPE result = start;

    // Accumulate elements in the array
add_loop:
    for (int i = 0; i < N; i++) {
        result += data[i];
    }
    return result;
}












#if 0

    #define W 6

FP_TYPE fp_add_array(FP_TYPE start)
{

	FP_TYPE result = start;
	FP_TYPE accum[W];
	for (int i = 0; i < W; i++)
		accum[i] = 0;
add_loop:
	for (int i = 0; i < N; i++)
	{
		accum[i % W] += data[i];
		// result += data[i];
	}

	for (int i = 0; i < W; i++)
    #pragma HLS UNROLL
		result += accum[i];
	return result;
}
#endif