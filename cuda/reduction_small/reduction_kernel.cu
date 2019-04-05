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
    Parallel reduction kernels
*/

#ifndef _REDUCE_KERNEL_H_
#define _REDUCE_KERNEL_H_

#include <stdio.h>
#include <cooperative_groups.h>

namespace cg = cooperative_groups;

// Utility class used to avoid linker errors with extern
// unsized shared memory arrays with templated type
template<class T>
struct SharedMemory
{
    __device__ inline operator       T *()
    {
        extern __shared__ int __smem[];
        return (T *)__smem;
    }

    __device__ inline operator const T *() const
    {
        extern __shared__ int __smem[];
        return (T *)__smem;
    }
};

// specialize for double to avoid unaligned memory
// access compile errors
template<>
struct SharedMemory<double>
{
    __device__ inline operator       double *()
    {
        extern __shared__ double __smem_d[];
        return (double *)__smem_d;
    }

    __device__ inline operator const double *() const
    {
        extern __shared__ double __smem_d[];
        return (double *)__smem_d;
    }
};

/*
    This version adds multiple elements per thread sequentially.  This reduces the overall
    cost of the algorithm while keeping the work complexity O(n) and the step complexity O(log n).
    (Brent's Theorem optimization)

    Note, this kernel needs a minimum of 64*sizeof(T) bytes of shared memory.
    In other words if blockSize <= 32, allocate 64*sizeof(T) bytes.
    If blockSize > 32, allocate blockSize*sizeof(T) bytes.
*/
template <class T, unsigned int blockSize>
__global__ void
reduce6(T *g_idata, T *g_odata, unsigned int n)
{
    // Handle to thread block group
    cg::thread_block cta = cg::this_thread_block();
    T *sdata = SharedMemory<T>();

    // perform first level of reduction,
    // reading from global memory, writing to shared memory
    unsigned int tid = threadIdx.x;
    unsigned int i = blockIdx.x*blockSize*2 + threadIdx.x;
    unsigned int gridSize = blockSize*2*gridDim.x;

    T mySum = 0;

    // we reduce multiple elements per thread.  The number is determined by the
    // number of active thread blocks (via gridDim).  More blocks will result
    // in a larger gridSize and therefore fewer elements per thread
    while (i < n)
    {
        mySum += g_idata[i];

        // ensure we don't read out of bounds -- this is optimized away for powerOf2 sized arrays
        if (i + blockSize < n)
            mySum += g_idata[i+blockSize];

        i += gridSize;
    }

    // each thread puts its local sum into shared memory
    sdata[tid] = mySum;
    cg::sync(cta);


    // do reduction in shared mem
    if ((blockSize >= 512) && (tid < 256))
    {
        sdata[tid] = mySum = mySum + sdata[tid + 256];
    }

    cg::sync(cta);

    if ((blockSize >= 256) &&(tid < 128))
    {
            sdata[tid] = mySum = mySum + sdata[tid + 128];
    }

    cg::sync(cta);

    if ((blockSize >= 128) && (tid <  64))
    {
       sdata[tid] = mySum = mySum + sdata[tid +  64];
    }

    cg::sync(cta);

    cg::thread_block_tile<32> tile32 = cg::tiled_partition<32>(cta);

    if (cta.thread_rank() < 32)
    {
        // Fetch final intermediate sum from 2nd warp
        if (blockSize >=  64) mySum += sdata[tid + 32];
        // Reduce final warp using shuffle
        for (int offset = tile32.size()/2; offset > 0; offset /= 2)
        {
             mySum += tile32.shfl_down(mySum, offset);
        }
    }

    // write result for this block to global mem
    if (cta.thread_rank() == 0) g_odata[blockIdx.x] = mySum;
}

////////////////////////////////////////////////////////////////////////////////
// Wrapper function for kernel launch
////////////////////////////////////////////////////////////////////////////////
template <class T>
void
reduce(int size, int threads, int blocks,
       T *d_idata, T *d_odata)
{
    dim3 dimBlock(threads, 1, 1);
    dim3 dimGrid(blocks, 1, 1);

    // when there is only one warp per block, we need to allocate two warps
    // worth of shared memory so that we don't index shared memory out of bounds
    int smemSize = (threads <= 32) ? 2 * threads * sizeof(T) : threads * sizeof(T);

    switch (threads)
    {
        case 512:
            reduce6<T, 512><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case 256:
            reduce6<T, 256><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case 128:
            reduce6<T, 128><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case 64:
            reduce6<T,  64><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case 32:
            reduce6<T,  32><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case 16:
            reduce6<T,  16><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case  8:
            reduce6<T,   8><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case  4:
            reduce6<T,   4><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case  2:
            reduce6<T,   2><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;

        case  1:
            reduce6<T,   1><<< dimGrid, dimBlock, smemSize >>>(d_idata, d_odata, size);
            break;
    }
}

// Instantiate the reduction function for 3 types
template void
reduce<int>(int size, int threads, int blocks,
            int *d_idata, int *d_odata);

template void
reduce<float>(int size, int threads, int blocks,
              float *d_idata, float *d_odata);

template void
reduce<double>(int size, int threads, int blocks,
               double *d_idata, double *d_odata);


#endif // #ifndef _REDUCE_KERNEL_H_
