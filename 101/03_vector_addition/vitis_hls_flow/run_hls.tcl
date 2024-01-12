# Command line argument parsing

if { $argc != 3 } {
    puts "################################################"
    puts "The script requires to indicate the flow to use"
    puts "Usage: vitis_hls -f [lindex $argv 1] -tclargs <flow: '0' for C simulation only, '1' for C simulation and synthesis>"
    puts "################################################"
    exit
}

set flow [lindex $argv 2]


# Create a project
open_project -reset proj_vector_addition

# Add design files that need to be synthesized
add_files vector_addition.cpp

# Add test bench & files
add_files -tb vector_addition_test.cpp

# Set the top-level function
set_top vector_add


# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
#set_part  {xcvu9p-flga2104-2-i}
# For Vivado ML standard edition we can use one of the included platforms
set_part {virtexuplusHBM} 
create_clock -period 200MHz

# Source x_hls.tcl to determine which steps to execute
csim_design

if {$flow == 1} {

    # Run Synthesis
    csynth_design

    # Run RTL cosim
    ##cosim_design
} elseif {$flow == 2} {

    # Run Synthesis
    csynth_design

    # Run RTL cosim
    cosim_design
}

exit
