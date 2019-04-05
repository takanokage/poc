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

#ifndef __REDUCTION_H__
#define __REDUCTION_H__

#define MAX_BLOCK_DIM_SIZE 65535

#ifndef MIN
#define MIN(x,y) ((x < y) ? x : y)
#endif

enum ReduceType
{
    REDUCE_INT,
    REDUCE_FLOAT,
    REDUCE_DOUBLE
};

const char * getReduceTypeString(const ReduceType type);

template<class T>
T reduceCPU(T *data, int size);

unsigned int nextPow2(unsigned int x);

void getNumBlocksAndThreads(int n, int maxBlocks, int maxThreads, int &blocks, int &threads);

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
                  T *d_odata);

template <class T>
void reduce(int size, int threads, int blocks,
            T *d_idata, T *d_odata);

template <class T>
bool runTest(ReduceType datatype);

#endif
