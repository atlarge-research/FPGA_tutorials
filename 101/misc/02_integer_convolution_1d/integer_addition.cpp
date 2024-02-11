// Function implementations
#include "integer_addition.h"
//#include "data.h"

#define N 1000


#if 0
void int_add_array(const int in[N], int out[N]) {


add_loop:
    for (int i = 2; i < N; i++) {
       	out[i] = (in[i] + in[i-1] + in[i-2])/3;
    }
//    return sum;
}

#endif


void int_add_array(const int in[N], int out[N]) {

	int prev = in[1];
	int prev_prev = in[0];
add_loop:
    for (int i = 2; i < N; i++) {
//#pragma HLS UNROLL factor=5
//        out[i] = (in[i] + in[i-1] + in[i-2])/3;
    	int cur = in[i];
    	int sum = (cur + prev + prev_prev);
    	out[i] = sum / 3;
    	prev_prev = prev;
    	prev = cur;
//    	sum += in[i] + in[i-1] + in[i-2];

    }
//    return sum;
}
