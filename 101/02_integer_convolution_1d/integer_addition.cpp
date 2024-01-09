// Function implementations
#include "integer_addition.h"
//#include "data.h"

#define N 1000

void int_add_array(const din_t in[N], dout_t out[N]) {

	din_t prev = in[1];
	din_t prev_prev = in[0];
add_loop:
    for (int i = 2; i < N; i++) {
//#pragma HLS UNROLL factor=5
//        out[i] = (in[i] + in[i-1] + in[i-2])/3;
    	din_t cur = in[i];
    	dout_t sum = (cur + prev + prev_prev);
    	out[i] = sum; // /3
    	prev_prev = prev;
    	prev = cur;
//    	sum += in[i] + in[i-1] + in[i-2];

    }
//    return sum;
}
