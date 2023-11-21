This example considers simple operations on integer numbers:
- addition of two integer numbers
- sum over an array of integer numbers (accumulation)

It includes the following files:
- `integer_addition.h` and `integer_addition.cpp`, the kernel files containing the declaration and definition of HLS functions respectively
- `integer_addition_test.cpp`, the testbench, that will be used to check the correctness of our kernels
- `data.h`, which contains static input data for the testbench.


**Note**: this example is tailored for command-line execution. Similar results and insight can be obtained by using Vitis HLS GUI. The GUI contains also 
useful tools, such as Scheduler Viewer and Graph Viewer, that do not have an equivalent command line interface.

## Summation of two integer numbers

Let's start by considering the summation of two integer numbers. Such kernel is defined in `integer_addition.cpp` as a function with name `int_add`.

```C++
int int_add(int a, int b) {
    // Sum the two numbers
    return a + b;
}
```

As you can notice, this simply takes in input two numbers and returns their sum. Let's now evaluate such a function.

### C Simulation

It is a common practice to evaluate the logical correctness of your HLS function before doing the synthesis. This can be done in Vitis HLS using the testbench and through the C Simulation flow. 

In the testbench file (`integer_addition_test.cpp`), we validate the results returned by the HLS function.

```C++
void test_int_add_a_b(int a, int b) {
    // Test simple addition
    int res = int_add(a, b);
    printf("Result of %d + %d = %d\n", a, b, res);
    assert(res == a + b);
}


int main() {
    // Test two numbers addition
    test_int_add_a_b(10, 12);
}
```

**Note**: in the `main` function leave only the `test_int_add_a_b` function uncommented.

To run the C synthesis, we need to execute the `tcl` script

```bash
vitis_hls -f run_hls.tcl -tclargs 0
```
where the command line argument `0` indicates the flow to execute (0 is for C simulation only).

At this point, the C simulation will be executed and this will print out the correctness check results (note that `vitis_hls` also outputs various logging messages)

```bash
INFO: [SIM 211-4] CSIM will launch GCC as the compiler.
   Compiling ../../../../integer_addition_test.cpp in debug mode
   Compiling ../../../../integer_addition.cpp in debug mode
   Generating csim.exe
Result of 10 + 12 = 22
INFO: [SIM 211-1] CSim done with 0 errors.
```

More details are in Chapters 12 and 13 of the Vitis HLS guide (v2022.2).

### Synthesis

Once we are satisfied with the results of the C simulation, we can proceed with synthesizing the kernels. The C/C++ source code is synthesized into an RTL implementation, from which the tool **estimates** resource utilization, performance, and final synthesis frequency.


```bash
vitis_hls -f run_hls.tcl -tclargs 1
```

**Note** in the `run_hls.tcl` script, the proper top function must be selected (line ~24, using the `set_top` command)

This command will generate various files under the `proj_integer_addition/syn` folder. You can inspect the generated `verilog` or `vhdl` code. Given the limited complexity of this example is easy to recognize the relevant parts. Under `report/` you can inspect the `int_add_csynt.rpt` report that contains (among the others):

- the targeted FPGA device (as defined in the tcl script)
- the clock timing estimates: in this case, we were targeting a design frequency of 200MHz (5 nsecs), but since this is a very simple program, it is likely that the final design can run at a higher frequency. In this case, it estimates the final clock at 0.880 nsecs (that is 1.13 GHz -- but results can change from synthesis to synthesis). Note that in the report there is also mentioned the clock uncertainty (27% of the target clock by default), which is used by the tool to account for any increases in net delays due to RTL logic synthesis, place, and route (please refer to the manuals if you want to know more).
- the latency: in some cases, this can be computed statically, and represents the number of clock cycles required for the function to compute all output values. In this case, this is 0 (the result is immediately computed)
- the resource utilization estimates: include the amount of hardware resources required to implement the design based on the resources available in the FPGA, e.g., look-up tables (LUT), registers, block RAMs, and DSP blocks. In this case, only 39 LUTs are needed to implement this function. 

The report folder contains another synthesis report (`csynth.rpt`), that contains similar information but is arranged in a different way. For example, this can be useful in the case you want to break down resource utilization per function.

**Note** The synthesis report is an important tool to quickly evaluate the expected performance of your design, and adjust it according to your needs. We will discuss this in the next example.

More info about synthesis in Chapter 14 of the Vitis HLS user guide (v2022.2).

### RTL Co-Simulation

After synthesis, we can run RTL Co-Simulation to verify that the RTL is functionally identical to the C source code. 
This could be also important to verify that the performance returned by the synthesis match the expectations and to overcome some of the limitations of C simulation (e.g., streams depth, implementation of floating point operations,... -- not relevant in this case but useful in more complicated use cases).

To run the co-simulation with the provided tcl script:

```bash
vitis_hls -f run_hls.tcl -tclargs 2
```

This will print in output various information, among the others:
```bash
INFO: [COSIM 212-316] Starting C post checking ...
Result of 10 + 12 = 22
INFO: [COSIM 212-1000] *** C/RTL co-simulation finished: PASS ***
INFO: [COSIM 212-210] Design is translated to an combinational logic. II and Latency will be marked as all 0.

```

## Sum over an array of integer numbers

In this use case, given an array of integer numbers (stored in the `data` array defined in `data.h`), we want to return the sum of all its elements. Accumulation is started from a given user value.
This function is implemented by the `int_add_array` function defined in `integer_addition.cpp`.

```C++
int int_add_array(int start) {
    // Accumulates the values in the array
    int result = start;

add_loop:
    for (int i = 0; i < 1000; i++) {
        result += data[i];
    }
    return result;
}
```

**Important** To work with this use case, the following changes must be done in the code base:
- inside the main function of the test bench file, we uncomment the appropriate test function (and comment the previous one):
```C++
int main() {
    // Test array accumulation, starting from 10
     test_int_add_array(10);
}
```
- in the tcl script, add the `int_add_array` function as the only top function (line 27). If you want to retain the results from the previous use case, you can also create a new project (through the `open_project` command), or a new solution (`open_solution`)

### C Simulation

Similarly to the previous use case, we can run C simulation to double-check the correctness of our C/C++ implementation:
```bash
vitis_hls -f run_hls.tcl -tclargs 0

...

INFO: [SIM 211-2] *************** CSIM start ***************
INFO: [SIM 211-4] CSIM will launch GCC as the compiler.
   Compiling ../../../../integer_addition_test.cpp in debug mode
   Compiling ../../../../integer_addition.cpp in debug mode
   Generating csim.exe
Result: 55230
Expected result: 55230
INFO: [SIM 211-1] CSim done with 0 errors.
INFO: [SIM 211-3] *************** CSIM finish ***************

```


### Synthesis

We can run the synthesis, look at the generated verilog/vhdl and inspect the reports for performance and resource usage:

```bash
vitis_hls -f run_hls.tcl -tclargs 1
```

In the `proj_integer_addition/solution1/syn/report/int_add_array_csynth.rpt` report we notice that:
- the resulting frequency is lower than before, due to a higher complexity in the design (2.438ns which is ~410 MHz)
- in this case, the latency to execute the program is 1,002 clock cycles. 
- in this case, the synthesized program requires 130 LUTs, 45 Flip-Flops, and 1 BRAM. In particular, the BRAM is used to store the input array (Note: in the memory subsection of the report you can note how the compiler has optimized the datatype given that it knows the actual numbers that will be stored)

In particular, under the "Details" section we find additional details for the (only) loop present in the code (`add_loop`, as labeled in the source code):
- it has an internal latency ($L$) of 2 clock cycles
- it has an Initiation Interval ($II$) of 1
- this loop is pipelined

*Why sometimes that takes 2 cycles to compute and is executed 1,000 times, completed in ~1,000 cycles*?

This is due to the loop pipelining. Indeed, an II of 1, means that  a new loop iteration can start on every clock cycle
We can derive the total computation time for a pipelined loop as $C = II(N-1) + L$, where $N$ is the number of loop iterations, 1,000 in this case.
Therefore, in this case the computation time is $C = 1(999) + 2 = 1,001$, which is very close to the expected program latency ($1,002$)


### Optimizing the loop

How can we make this loop run faster? We can leverage the spatial parallelism offered by the device (we are using less than 1% of the entire resources!).

Similarly to what is done in CPU with vectorization, in this case, we can compute multiple sums in parallel. We can achieve this by using the pragma `HLS unroll`, right below the guard of the loop we want to parallelize.

Let's assume that we want to unroll with a factor of 5 (note: the unrolling factor must be known at compile time). The function code changes in:

```C++
int int_add_array(int start) {
    // Accumulates the values in the array
    int result = start;

add_loop:
    for (int i = 0; i < 1000; i++) {
    #pragma HLS unroll factor = 5
        result += data[i];
    }
    return result;
}
```

After re-running the synthesis, we can notice from the report that now:
- the total execution time is ~200 clock cycles. This is because the `add_loop` will now run for 200 iterations, each one computing in parallel over 5 numbers
- the resource usage is increased, in particular, more BRAM is used, since each BRAM can support at most 2 parallel reads per cycle (Note: The Vivado tools automatically determine if a block RAM is used in Single or True Data port mode, and therefore the actual number of used BRAM depends on internal tool choice). 


### RTL Co-Simulation

As before, we can run the RTL Co-Simulation to double-check the RTL implementation.

```bash
vitis_hls -f run_hls.tcl -tclargs 2
```

Under `proj_integer_addition/solution1/sim/report.int_add_array_cosim.rpt` we can check the actual latency of the program (201 cycles for the unrolled version, vs. the 203 estimated during synthesis).