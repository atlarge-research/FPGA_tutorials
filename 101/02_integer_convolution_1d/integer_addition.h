/*
    Sums all element over the array, and adds to the starting value
*/

#include "ap_int.h"
#define N 128

typedef ap_int<7> din_t;
typedef ap_int<10> dout_t;

void int_add_array(const din_t [N], dout_t[N]);
