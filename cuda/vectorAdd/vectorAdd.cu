
#include "vectorAdd.cuh"

// ---------------------------------------------------------------------------
// C = A + B
// ---------------------------------------------------------------------------
__global__ void vectorAdd(
    const float* A,
    const float* B,
    float* const C,
    int numElements)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements)
        C[i] = A[i] + B[i];
}
