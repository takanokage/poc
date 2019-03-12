
#ifndef VECTOR_ADD_H
#define VECTOR_ADD_H

__global__ void vectorAdd(
    const float* A,
    const float* B,
    float* const C,
    int numElements);

#endif
