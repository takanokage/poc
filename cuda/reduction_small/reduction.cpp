/*
 * Copyright 1993-2015 NVIDIA Corporation.  All rights reserved.
 *
 * Please refer to the NVIDIA end user license agreement (EULA) associated
 * with this source code for terms and conditions that govern your use of
 * this software. Any use, reproduction, disclosure, or distribution of
 * this software and related documentation outside the terms of the EULA
 * is strictly prohibited.
 *
 */


/*
    Parallel reduction

    This sample shows how to perform a reduction operation on an array of values
    to produce a single value.

    Reductions are a very common computation in parallel algorithms.  Any time
    an array of values needs to be reduced to a single value using a binary
    associative operator, a reduction can be used.  Example applications include
    statistics computations such as mean and standard deviation, and image
    processing applications such as finding the total luminance of an
    image.

    This code performs sum reductions, but any associative operator such as
    min() or max() could also be used.

    It assumes the input size is a power of 2.

    COMMAND LINE ARGUMENTS

    "--shmoo":         Test performance for 1 to 32M elements with each of the 7 different kernels
    "--n=<N>":         Specify the number of elements to reduce (default 1048576)
    "--threads=<N>":   Specify the number of threads per block (default 128)
    "--kernel=<N>":    Specify which kernel to run (0-6, default 6)
    "--maxblocks=<N>": Specify the maximum number of thread blocks to launch (kernel 6 only, default 64)
    "--cpufinal":      Read back the per-block results and do final sum of block sums on CPU (default false)
    "--cputhresh=<N>": The threshold of number of blocks sums below which to perform a CPU final reduction (default 1)
    "-type=<T>":       The datatype for the reduction, where T is "int", "float", or "double" (default int)
*/

// CUDA Runtime
#include <cuda_runtime.h>

#include <algorithm>
#include <strings.h>

#include "performance.h"
#include "reduction.h"

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char **argv)
{
    printf("%s Starting...\n\n", argv[0]);

    ReduceType datatype = REDUCE_FLOAT;

    cudaError_t status = cudaSuccess;
    cudaDeviceProp deviceProp;
    int dev = 0;
    status = cudaGetDeviceProperties(&deviceProp, dev);

    printf("Using Device %d: %s\n\n", dev, deviceProp.name);
    status = cudaSetDevice(dev);

    printf("Reducing array of type %s\n\n", getReduceTypeString(datatype));

    bool bResult = false;

    switch (datatype)
    {
        default:
        case REDUCE_INT:
            bResult = runTest<int>();
            break;

        case REDUCE_FLOAT:
            bResult = runTest<float>();
            break;

        case REDUCE_DOUBLE:
            bResult = runTest<double>();
            break;
    }

    printf(bResult ? "Test passed\n" : "Test failed!\n");
}

const char * getReduceTypeString(const ReduceType type)
{
    switch (type)
    {
    case REDUCE_INT:
        return "int";
    case REDUCE_FLOAT:
        return "float";
    case REDUCE_DOUBLE:
        return "double";
    default:
        return "unknown";
    }
}

////////////////////////////////////////////////////////////////////////////////
//! Compute sum reduction on CPU
//! We use Kahan summation for an accurate sum of large arrays.
//! http://en.wikipedia.org/wiki/Kahan_summation_algorithm
//!
//! @param data       pointer to input data
//! @param size       number of input data elements
////////////////////////////////////////////////////////////////////////////////
template<class T>
T reduceCPU(T *data, int size)
{
    T sum = data[0];
    T c = (T)0.0;

    for (int i = 1; i < size; i++)
    {
        T y = data[i] - c;
        T t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}

unsigned int nextPow2(unsigned int x)
{
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}

////////////////////////////////////////////////////////////////////////////////
// Compute the number of threads and blocks to use for the given reduction kernel
// we set threads / block to the minimum of maxThreads and n/2.
// we observe the maximum specified number of blocks, because each thread in
// that kernel can process a variable number of elements.
////////////////////////////////////////////////////////////////////////////////
void getNumBlocksAndThreads(int n, int maxBlocks, int maxThreads, int &blocks, int &threads)
{
    cudaError_t status = cudaSuccess;

    //get device capability, to avoid block/grid size exceed the upper bound
    cudaDeviceProp prop;
    int device;
    status = cudaGetDevice(&device);
    status = cudaGetDeviceProperties(&prop, device);

    threads = (n < maxThreads*2) ? nextPow2((n + 1)/ 2) : maxThreads;
    blocks = (n + (threads * 2 - 1)) / (threads * 2);

    if ((float)threads*blocks > (float)prop.maxGridSize[0] * prop.maxThreadsPerBlock)
    {
        printf("n is too large, please choose a smaller number!\n");
    }

    if (blocks > prop.maxGridSize[0])
    {
        printf("Grid size <%d> exceeds the device capability <%d>, set block size as %d (original %d)\n",
               blocks, prop.maxGridSize[0], threads*2, threads);

        blocks /= 2;
        threads *= 2;
    }

    blocks = MIN(maxBlocks, blocks);
}

////////////////////////////////////////////////////////////////////////////////
// This function performs a reduction of the input data multiple times and
// measures the average reduction time.
////////////////////////////////////////////////////////////////////////////////
template <class T>
T benchmarkReduce(int  n,
                  int  numThreads,
                  int  numBlocks,
                  int  maxThreads,
                  int  maxBlocks,
                  int  testIterations,
                  bool cpuFinalReduction,
                  int  cpuFinalThreshold,
                  double *duration,
                  T *h_odata,
                  T *d_idata,
                  T *d_odata)
{
    cudaError_t status = cudaSuccess;
    T gpu_result = 0;
    bool needReadBack = true;

    for (int i = 0; i < testIterations; ++i)
    {
        gpu_result = 0;

        cudaDeviceSynchronize();
        Performance::Start();

        // execute the kernel
        reduce<T>(n, numThreads, numBlocks, d_idata, d_odata);

        cudaError_t status = cudaSuccess;
        // check if kernel execution generated an error
        status = cudaGetLastError();

        if (cpuFinalReduction)
        {
            // sum partial sums from each block on CPU
            // copy result from device to host
            status = cudaMemcpy(h_odata, d_odata, numBlocks*sizeof(T), cudaMemcpyDeviceToHost);

            for (int i=0; i<numBlocks; i++)
            {
                gpu_result += h_odata[i];
            }

            needReadBack = false;
        }
        else
        {
            // Clear d_idata for later use as temporary buffer.
            cudaMemset(d_idata, 0, n*sizeof(T));

            // sum partial block sums on GPU
            int s=numBlocks;

            while (s > cpuFinalThreshold)
            {
                int threads = 0, blocks = 0;
                getNumBlocksAndThreads(s, maxBlocks, maxThreads, blocks, threads);
                cudaMemcpy(d_idata, d_odata, s*sizeof(T), cudaMemcpyDeviceToDevice);
                reduce<T>(s, threads, blocks, d_idata, d_odata);

                s = (s + (threads*2-1)) / (threads*2);
            }

            if (s > 1)
            {
                // copy result from device to host
                status = cudaMemcpy(h_odata, d_odata, s * sizeof(T), cudaMemcpyDeviceToHost);

                for (int i=0; i < s; i++)
                {
                    gpu_result += h_odata[i];
                }

                needReadBack = false;
            }
        }

        cudaDeviceSynchronize();
        Performance::Stop();
    }

    if (needReadBack)
    {
        // copy final sum from device to host
        status = cudaMemcpy(&gpu_result, d_odata, sizeof(T), cudaMemcpyDeviceToHost);
    }

    *duration = Performance::Duration() * 1e-3;

    return gpu_result;
}

////////////////////////////////////////////////////////////////////////////////
// The main function which runs the reduction test.
////////////////////////////////////////////////////////////////////////////////
template <class T>
bool
runTest()
{
    cudaError_t status = cudaSuccess;

    int size = 1<<26;    // number of elements to reduce
    int maxThreads = 256;  // number of threads per block
    int maxBlocks = 64;
    bool cpuFinalReduction = false;
    int cpuFinalThreshold = 1;

    printf("%d elements\n", size);
    printf("%d threads (max)\n", maxThreads);

    // create random input data on CPU
    unsigned int bytes = size * sizeof(T);

    T *h_idata = (T *) malloc(bytes);

    for (int i=0; i<size; i++)
    {
        // Keep the numbers small so we don't get truncation error in the sum
        if (std::is_integral<T>())
            h_idata[i] = (T)(rand() & 0xFF);
        else
            h_idata[i] = (rand() & 0xFF) / (T)RAND_MAX;
    }

    int numBlocks = 0;
    int numThreads = 0;
    getNumBlocksAndThreads(size, maxBlocks, maxThreads, numBlocks, numThreads);

    if (numBlocks == 1)
    {
        cpuFinalThreshold = 1;
    }

    // allocate mem for the result on host side
    T *h_odata = (T *) malloc(numBlocks*sizeof(T));

    printf("%d blocks\n\n", numBlocks);

    // allocate device memory and data
    T *d_idata = NULL;
    T *d_odata = NULL;

    status = cudaMalloc((void **) &d_idata, bytes);
    status = cudaMalloc((void **) &d_odata, numBlocks*sizeof(T));

    // copy data directly to device memory
    status = cudaMemcpy(d_idata, h_idata, bytes, cudaMemcpyHostToDevice);
    status = cudaMemcpy(d_odata, h_idata, numBlocks*sizeof(T), cudaMemcpyHostToDevice);

    // warm-up
    reduce<T>(size, numThreads, numBlocks, d_idata, d_odata);

    int testIterations = 100;

    double reduceTime = 0.0;
    T gpu_result = 0;

    gpu_result = benchmarkReduce<T>(size, numThreads, numBlocks, maxThreads, maxBlocks,
                                    testIterations, cpuFinalReduction,
                                    cpuFinalThreshold, &reduceTime,
                                    h_odata, d_idata, d_odata);

    printf("Reduction, Throughput = %.4f GB/s, Time = %.5f s, Size = %u Elements, NumDevsUsed = %d, Workgroup = %u\n",
            1.0e-9 * ((double)bytes)/reduceTime, reduceTime, size, 1, numThreads);

    // compute reference solution
    T cpu_result = reduceCPU<T>(h_idata, size);

    int precision = 0;
    double threshold = 0;
    double diff = 0;

    if (std::is_same<T, int>())
    {
        printf("\nGPU result = %d\n", (int)gpu_result);
        printf("CPU result = %d\n\n", (int)cpu_result);
    }
    else
    {
        if (std::is_same<T, float>())
        {
            precision = 8;
            threshold = 1e-8 * size;
        }
        else
        {
            precision = 12;
            threshold = 1e-12 * size;
        }

        printf("\nGPU result = %.*f\n", precision, (double)gpu_result);
        printf("CPU result = %.*f\n\n", precision, (double)cpu_result);

        diff = fabs((double)gpu_result - (double)cpu_result);
    }

    // cleanup
    free(h_idata);
    free(h_odata);

    status = cudaFree(d_idata);
    status = cudaFree(d_odata);

    if (std::is_same<T, int>())
    {
        return (gpu_result == cpu_result);
    }
    else
    {
        return (diff < threshold);
    }

    return true;
}
