#include <string>

const std::string mc33_kernel =
    "__kernel \n"
    "void mc33(__global float *A,__global float *B){ \n"
    "  int idx = get_global_id(0); \n"
    "  B[idx] = A[idx]; \n"
    "}";
