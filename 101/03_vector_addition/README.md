# Targeting hardware

The goals of this example:
- show the differences between `Vitis HLS` and `Vitis` flow
- discuss how programming using Vitis for on-device execution
- discuss how interfacing host and FPGA
- discuss on how using external memory (device DRAM), and how to optimize for its use (TBD)

As running example, we will consider the sum of two vectors ($x$ and $y$) of $N$ elements
This example is based on the Vitis Accel "Hello World" example.

## The Vitis HLS flow

The `vitis_hls_flow`  folder contains the FPGA kernel (`vector_addition.cpp` and `vector_addition.h`), test bench (`vector_addition_test.cpp`) and TCL script (`run_hls.tcl`), to experiment with the Vitis HLS flow as discussed in the previous two examples (`01_integer_addition`, and `02_fp_addition`).


## The Vitis flow

The `vitis_flow` folder, contains all the code relative for simulating, co-simulating, compiling and run the kernel on an actual FPGA device using AMD/Xilinx Vitis.

It contains:
- `src/host.cpp` the host file, that is in charge of loading the bitstream, creating the OpenCL context, program, kernel, buffer and queues to program the device, copying data to the device, running the computation, and copying back the result to the host
- `src/krnl_vector_addition.cpp` contains the FPGA kernel code
- `Makefile` contains command to build and run the program for X86 Simulation (`TARGET=sw_emu`), RTL Co-simulation (`TARGET=hw_emu`) or Hardware (`TARGET=hw`). Currently it targets a specific platform, consider changing it according to your system.