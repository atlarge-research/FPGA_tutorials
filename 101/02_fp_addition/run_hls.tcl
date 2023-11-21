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
open_project -reset proj_fp_addition

# Add design files that need to be synthesized
add_files fp_addition.cpp

# Add test bench & files
add_files -tb fp_addition_test.cpp

# Set the top-level function (uncomment the proper top function)
set_top fp_add
#set_top fp_add_array

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part  {xcvu9p-flga2104-2-i}
create_clock -period 200MHz

# Source x_hls.tcl to determine which steps to execute
csim_design

if {$flow == 1} {

    # Run Synthesis
    csynth_design

    # Run RTL cosim
} elseif {$flow == 2} {

    # Run Synthesis
    csynth_design

    # Run RTL cosim
    cosim_design
}

exit