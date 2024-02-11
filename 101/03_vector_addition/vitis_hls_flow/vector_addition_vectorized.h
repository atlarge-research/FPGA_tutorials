/*
    Returns the sum of the input vectors: z = x + y
*/
#include <hls_vector.h>
typedef hls::vector<int, 8> t_int8Vec;
void vector_add(t_int8Vec* x, t_int8Vec* y, t_int8Vec *z, const int N);
