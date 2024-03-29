#pragma once

/*
    Definition of the used floating point type (can be single -- float -- or double precision)
*/
typedef float FP_TYPE;

const int N = 1000;  // Number of elements
static float data[N] = {1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53,
                        1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53, 1.1, 2, 3, 4.5, 1.8, 9.3, 10.4, 5.6, 7.3, 2.53};