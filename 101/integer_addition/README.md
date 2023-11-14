This example consider simple operations on integer numbers:
- addition of two integer numbers
- sum over an array of integer numbers (accumulation)

It includes the following files:
- `integer_addition.h` and `integer_addition.cpp`, the kernel files containing respectively the declaration and definition of HLS functions
- `integer_addition_test.cpp`, the testbench, that will be used to check the correctness of our kernels
- `data.h`, that contains static input data for the testbench.


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

As you can notice, this simply takes in input two numbers and returns their sum. Let's now evaluate such function.

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

More details in Chapters 12 and 13 of Vitis HLS guide (v2022.2).

### Synthesis

Once we are satisfied with the results of C simulation, we can proceed with synthesizing the kernels. The C/C++ source code is synthesized into an RTL implementation, from which the tool **estimates** resource utilization, performance, and final synthesis frequency.


```bash
vitis_hls -f run_hls.tcl -tclargs 1
```

**Note** in the `run_hls.tcl` script, the proper top function must be selected (line ~26, using the `set_top` command)

This commnd will generate various files under the `proj_integer_addition/syn` folder. You can inspect the generated `verilog` or `vhdl` code. Given the limited complexity of this example is easy to recognize the relevant parts. Under `report/` you can inspect the `int_add_csynt.rpt` report that contains (among the others):

- the targeted FPGA device (as defined in the tcl script)
- the clock timing estimates: in this case we were targeting a design frequency of 200MHz (5 nsecs), but since this is a very simple program, it is likely that the final design can run at higher frequency. In this case, it estimating the final clock at 0.880 nsecs (that is 1.13 GHz -- but results can change from synthesis to synthesis). Note that in the report there is also mentioned the clock uncertainty (27% of the target clock by default), that is used by the tool to to account for any increases in net delays due to RTL logic synthesis, place, and route (please refer to the manuals if you want to know more).
- the latency: in some cases this can be computed statically, and represents the number of clock cycles required for the function to compute all output values. In this case this is 0 (the result is immediately computed)
- the resource utilization estimates: includes the amount of hardware resources required to implement the design based on the resources available in the FPGA, e.g., look-up tables (LUT), registers, block RAMs, and DSP blocks. In this case, only 39 LUTs are needed to implement this function. 

The report folder contains another synthesis report (`csynth.rpt`), that contains similar informations but arranged in a different way. For example, this can be useful in the case you want to break down resource utilization per function.

**Note** the synthesis report is an important tool to quickly evaluate the expected performance of your design, and adjust it according to your needs. We will discuss this in the next example.

More info about synthesis in Chapter 14 of the Vitis HLS user guide (v2022.2).

### RTL Co-Simulation

After synthesis, we can run RTL Co-Simulation to verify that the RTL is functionally identical to the C source code. 
This could be also important to verify that the performance returned by the synthesis match the expectations and to overcome some of the limitation of C simulation (e.g., streams depth, implementation of floating point operations,... -- not relevant in this case but useful in more complicated use cases).

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
- inside the main function function of the test bench file, we uncomment the appropriate test function (and comment the previous one):
```C++

```




- Csim
- Synthesis, generates two rpt file under `syn/`. Some of this information can also be inferred by log files
- TODO Discuss what kind of information can be found in the two different report (the one with the name of the file is better, but the other contains more info)

- The output is saved under `vitis_hls.log`