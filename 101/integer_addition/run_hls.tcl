# Create a project
open_project -reset proj_integer_addition

# Add design files that need to be synthesized
add_files integer_addition.cpp

# Add test bench & files
add_files -tb integer_addition_test.cpp

# Set the top-level function
set_top int_add

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcvu9p-flga2104-2-i}
create_clock -period 200MHz

# Source x_hls.tcl to determine which steps to execute
csim_design

# Set any optimization directives
#set_directive_inline -off sub_func
# End of directives

# Run Synthesis
csynth_design

# Run RTL cosim
cosim_design
