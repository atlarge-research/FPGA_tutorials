/* TODOs:

- create the kernel (copy-paste + extern + memory interface)
- Makefile, host is ok, the rest must be done (also why cfg is not needed here?). PLATFORM is missing and maybe also other info from general Makefile 
    (see Xilinx repo, either the helloworld or the cpp adder example)
- make sure the three flows work
- READMEs

*/


extern "C"{

    void vector_add(int* x, int* y, int *z, const int N) {
        #pragma HLS INTERFACE m_axi port = x bundle = gmem0
        #pragma HLS INTERFACE m_axi port = y bundle = gmem1
        #pragma HLS INTERFACE m_axi port = z bundle = gmem0

        // Sum the two vectors
        add_loop: for (int i = 0; i < N; i++) {
            z[i] = x[i] + y[i] ;
        }

    }

}

