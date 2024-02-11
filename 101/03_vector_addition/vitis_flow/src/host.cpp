/**
 * Host program for vector addition.
 * This is based on the Xilinx Vitis Accel example ("simple_vadd") and uses the OpenCL bindings
*/

#define OCL_CHECK(error, call)                                                                   \
    call;                                                                                        \
    if (error != CL_SUCCESS) {                                                                   \
        printf("%s:%d Error calling " #call ", error code is: %d\n", __FILE__, __LINE__, error); \
        exit(EXIT_FAILURE);                                                                      \
    }


#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl2.hpp>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <chrono>



static const std::string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";

int main(int argc, char* argv[]) {
    // TARGET_DEVICE macro needs to be passed from gcc command line
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <xclbin>" << std::endl;
        return EXIT_FAILURE;
    }

    // Read the vector length
    int vector_length;
    std::cout << "Insert vector size: " << std::endl;
    std::cin >> vector_length;

    std::string xclbinFilename = argv[1];

    // Compute the size of array in bytes
    size_t size_in_bytes = vector_length * sizeof(int);
    std::cout << "Data size: " << size_in_bytes/1024/1024 << " MB" << std::endl;

    /*******************************
    * Open and load the bitstream
    ********************************/
    std::cout << "INFO: Reading " << xclbinFilename << std::endl;
    FILE* fp;
    if ((fp = fopen(xclbinFilename.c_str(), "r")) == nullptr) {
        printf("ERROR: %s xclbin not available please build\n", xclbinFilename.c_str());
        exit(EXIT_FAILURE);
    }
    // Load xclbin
    std::cout << "Loading: '" << xclbinFilename << "'\n";
    std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
    bin_file.seekg(0, bin_file.end);
    unsigned nb = bin_file.tellg();
    bin_file.seekg(0, bin_file.beg);
    char* buf = new char[nb];
    bin_file.read(buf, nb);

    // Creating Program from Binary File
    cl::Program::Binaries bins;
    bins.push_back({buf, nb});
    bool valid_device = false;



    std::vector<cl::Device> devices;
    cl_int err;
    cl::Context context;
    cl::CommandQueue q;
    cl::Kernel krnl_vector_add;
    std::vector<cl::Platform> platforms;
    bool found_device = false;

    // traversing all Platforms To find Xilinx Platform and targeted
    // Device in Xilinx Platform.
    // Note: if you know the platform name, you can directly look for that
    cl::Platform::get(&platforms);
    for (size_t i = 0; (i < platforms.size()) & (found_device == false); i++) {
        cl::Platform platform = platforms[i];
        std::string platformName = platform.getInfo<CL_PLATFORM_NAME>();
        if (platformName == "Xilinx") {
            devices.clear();
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
            if (devices.size()) {
                found_device = true;
                break;
            }
        }
    }
    if (found_device == false) {
        std::cout << "Error: Unable to find Target Device " << std::endl;
        return EXIT_FAILURE;
    }

    // Use the first available device

    auto device = devices[0];
    // Creating Context and Command Queue for selected Device
    OCL_CHECK(err, context = cl::Context(device, nullptr, nullptr, nullptr, &err));
    OCL_CHECK(err, q = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err));
    std::cout << "Trying to program device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    cl::Program program(context, {device}, bins, nullptr, &err);
    if (err != CL_SUCCESS) {
        std::cout << "Failed to program device with xclbin file!\n";
    } else {
        std::cout << "Device: program successful!\n";
        OCL_CHECK(err, krnl_vector_add = cl::Kernel(program, "vector_add", &err));
        valid_device = true;
    }
    
    if (!valid_device) {
        std::cout << "Failed to program any device found, exit!\n";
        exit(EXIT_FAILURE);
    }

    /********************************************
    * Allocate buffers on device and prepare data
    **********************************************/

    // These commands will allocate memory on the Device. The cl::Buffer objects can
    // be used to reference the memory locations on the device.
    OCL_CHECK(err, cl::Buffer buffer_x(context, CL_MEM_READ_ONLY, size_in_bytes, NULL, &err));
    OCL_CHECK(err, cl::Buffer buffer_y(context, CL_MEM_READ_ONLY, size_in_bytes, NULL, &err));
    OCL_CHECK(err, cl::Buffer buffer_z(context, CL_MEM_WRITE_ONLY, size_in_bytes, NULL, &err));

    // set the kernel Arguments
    int narg = 0;
    OCL_CHECK(err, err = krnl_vector_add.setArg(narg++, buffer_x));
    OCL_CHECK(err, err = krnl_vector_add.setArg(narg++, buffer_y));
    OCL_CHECK(err, err = krnl_vector_add.setArg(narg++, buffer_z));
    OCL_CHECK(err, err = krnl_vector_add.setArg(narg++, vector_length));

    // We then need to map our OpenCL buffers to get the pointers
    int* ptr_x;
    int* ptr_y;
    int* ptr_z; //the result
    OCL_CHECK(err,
              ptr_x = (int*)q.enqueueMapBuffer(buffer_x, CL_TRUE, CL_MAP_WRITE, 0, size_in_bytes, NULL, NULL, &err));
    OCL_CHECK(err,
              ptr_y = (int*)q.enqueueMapBuffer(buffer_y, CL_TRUE, CL_MAP_WRITE, 0, size_in_bytes, NULL, NULL, &err));
    OCL_CHECK(err, ptr_z = (int*)q.enqueueMapBuffer(buffer_z, CL_TRUE, CL_MAP_READ, 0, size_in_bytes, NULL,
                                                         NULL, &err));
    int test;
    
    // Initialize the vectors used in the test
    for (int i = 0; i < vector_length; i++) {
        ptr_x[i] = rand() % 1024;
        ptr_y[i] = rand() % 1024;
    }
    
    // Data will be migrated to kernel space
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_x, buffer_y}, 0 /* 0 means from host*/));
    std::cin >> test;
    OCL_CHECK(err, q.finish());

    std::cout << "Copied data to device "<<std::endl;
    /*********************
    * Run the kernel 
    ********************/
    //finish previous commands

    const unsigned long int start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    // Launch the Kernel
    OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));

    // wait for its execution
    OCL_CHECK(err, q.finish());
    const unsigned long int end_time_us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

    std::cout << "Kernel execution completed in (usecs): " << end_time_us - start_time_us << std::endl;


    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will transfer the data from FPGA to
    // source_results vector
    OCL_CHECK(err, q.enqueueMigrateMemObjects({buffer_z}, CL_MIGRATE_MEM_OBJECT_HOST));

    OCL_CHECK(err, q.finish());


    /**********************
     * Verify the results
    *************************/
    int match = 0;
    for (int i = 0; i < vector_length; i++) {
        int host_result = ptr_x[i] + ptr_y[i];
        if (ptr_z[i] != host_result) {
            printf(error_message.c_str(), i, host_result, ptr_z[i]);
            match = 1;
            break;
        }
    }

    /********************
     * Cleanup
    *********************/
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_x, ptr_x));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_y, ptr_y));
    OCL_CHECK(err, err = q.enqueueUnmapMemObject(buffer_z, ptr_z));
    OCL_CHECK(err, err = q.finish());

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl;
    return (match ? EXIT_FAILURE : EXIT_SUCCESS);
}