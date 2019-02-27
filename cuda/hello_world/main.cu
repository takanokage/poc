
#include "main.cuh"

#include <cuda_runtime.h>

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    // Error code to check return values for CUDA calls
    cudaError_t err = cudaSuccess;

    // Print the vector length to be used, and compute its size
    int numElements = 1 << 19;
    cout << "Vector addition of " << numElements << " elements" << endl;

    // host memory
    float *h_A = NULL;
    float *h_B = NULL;
    float *h_C = NULL;

    // device memory
    float *d_A = NULL;
    float *d_B = NULL;
    float *d_C = NULL;

    if (!AlocateHstMemory(&h_A, numElements, "h_A")) exit(1);
    if (!AlocateHstMemory(&h_B, numElements, "h_B")) exit(1);
    if (!AlocateHstMemory(&h_C, numElements, "h_C")) exit(1);

    RandInit(h_A, numElements);
    RandInit(h_B, numElements);

    if (!AlocateDevMemory(&d_A, numElements, "d_A")) exit(1);
    if (!AlocateDevMemory(&d_B, numElements, "d_B")) exit(1);
    if (!AlocateDevMemory(&d_C, numElements, "d_C")) exit(1);

    // Copy input to the device
    CopyHst2DevMemory(h_A, d_A, numElements);
    CopyHst2DevMemory(h_B, d_B, numElements);

    // Launch the Vector Add CUDA Kernel
    int threadsPerBlock = 256;
    int blocksPerGrid =(numElements + threadsPerBlock - 1) / threadsPerBlock;

    cout << "CUDA kernel launch with " << blocksPerGrid;
    cout << " blocks of " << threadsPerBlock << " threads" << endl;

    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, numElements);
    err = cudaGetLastError();

    if (err != cudaSuccess)
    {
        cout << "status: " << cudaGetErrorString(err) << endl;
        cout << "Failed to launch vectorAdd kernel" << endl;
        exit(1);
    }

    // Copy results to the host
    CopyDev2HstMemory(d_C, h_C, numElements);

    // Verify that the result vector is correct
    for (int i = 0; i < numElements; ++i)
    {
        if (fabs(h_A[i] + h_B[i] - h_C[i]) > 1e-5)
        {
            cout << "Result verification failed at element " << i << endl;
            exit(1);
        }
    }

    cout << "Test PASSED" << endl;

    // Free device global memory
    freeDev(d_A);
    freeDev(d_B);
    freeDev(d_C);

    // Free host memory
    free(h_A);
    free(h_B);
    free(h_C);

    cout << "Done" << endl;
    cout << endl;

    return 0;
}

// ---------------------------------------------------------------------------
// Alocate host memory and perform validation.
// ---------------------------------------------------------------------------
bool AlocateHstMemory(float** h, const int& numElements, const string& name)
{
    size_t size = numElements * sizeof(float);

    *h = (float *)malloc(size);

    if (*h != NULL)
        return true;

    cout << "Failed to allocate host memory: " << name << endl;

    return false;
}

// ---------------------------------------------------------------------------
// Alocate device memory and perform validation.
// ---------------------------------------------------------------------------
bool AlocateDevMemory(float** d, const int& numElements, const string& name)
{
    cudaError_t err = cudaSuccess;

    size_t size = numElements * sizeof(float);

    err = cudaMalloc((void **)d, size);

    if (err == cudaSuccess)
        return true;

    cout << "status: " << cudaGetErrorString(err) << endl;
    cout << "Failed to allocate device memory: " << name << endl;

    return false;
}

// ---------------------------------------------------------------------------
// Initialize host memory.
// ---------------------------------------------------------------------------
void RandInit(float* h, const int& numElements)
{
    for (int i = 0; i < numElements; ++i)
        h[i] = rand()/(float)RAND_MAX;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
bool CopyHst2DevMemory(float* h, float* d, const int& numElements)
{
    cudaError_t err = cudaSuccess;

    size_t size = numElements * sizeof(float);

    cout << "Copy host memory to the CUDA device." << endl;
    err = cudaMemcpy(d, h, size, cudaMemcpyHostToDevice);

    if (err == cudaSuccess)
        return true;

    cout << "status: " << cudaGetErrorString(err) << endl;
    cout << "Failed to copy host memory to the CUDA device." << endl;

    return false;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
bool CopyDev2HstMemory(float* d, float* h, const int& numElements)
{
    cudaError_t err = cudaSuccess;

    size_t size = numElements * sizeof(float);

    cout << "Copy device memory to the host." << endl;
    err = cudaMemcpy(h, d, size, cudaMemcpyDeviceToHost);

    if (err == cudaSuccess)
        return true;

    cout << "status: " << cudaGetErrorString(err) << endl;
    cout << "Failed to copy device memory to the host." << endl;

    return false;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
bool freeDev(float* d_A)
{
    cudaError_t err = cudaSuccess;

    err = cudaFree(d_A);

    if (err == cudaSuccess)
        return true;

    cout << "status: " << cudaGetErrorString(err) << endl;
    cout << "Failed to free device vector A" << endl;

    return false;
}
