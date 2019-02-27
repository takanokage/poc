
#ifndef MAIN_H
#define MAIN_H

#include "cusolverDn.h"

void DeviceInfo(const int& devID);

template<typename T>
void testLU(const int& devID, const int& size);

template<typename T>
void Residual(
    const cublasHandle_t& cublasHandle,
    T* d_A,
    T* d_x,
    T* d_r,
    const int& N) { return CUSOLVER_STATUS_INVALID_VALUE; };

template<>
void Residual<double>(
    const cublasHandle_t& cublasHandle,
    double* d_A,
    double* d_x,
    double* d_r,
    const int& N);

template<>
void Residual<float>(
    const cublasHandle_t& cublasHandle,
    float* d_A,
    float* d_x,
    float* d_r,
    const int& N);

template<typename T>
cusolverStatus_t cusolverDngetrf_bufferSize(
    const cusolverDnHandle_t& handle,
    const T* const A,
    const int& size,
    int* Lwork) { return CUSOLVER_STATUS_INVALID_VALUE; };

template<>
cusolverStatus_t cusolverDngetrf_bufferSize<double>(
    const cusolverDnHandle_t& handle,
    const double* const A,
    const int& size,
    int* Lwork);

template<>
cusolverStatus_t cusolverDngetrf_bufferSize<float>(
    const cusolverDnHandle_t& handle,
    const float* const A,
    const int& size,
    int* Lwork);

template<typename T>
cusolverStatus_t cusolverDngetrf(
    const cusolverDnHandle_t& handle,
    T* A,
    const int& size,
    T* Workspace,
    int* devIpiv,
    int* devInfo) { return CUSOLVER_STATUS_INVALID_VALUE; };

template<>
cusolverStatus_t cusolverDngetrf<double>(
    const cusolverDnHandle_t& handle,
    double* A,
    const int& size,
    double* Workspace,
    int* devIpiv,
    int* devInfo);

template<>
cusolverStatus_t cusolverDngetrf<float>(
    const cusolverDnHandle_t& handle,
    float* A,
    const int& size,
    float* Workspace,
    int* devIpiv,
    int* devInfo);

template<typename T>
cusolverStatus_t cusolverDngetrs(
    const cusolverDnHandle_t& handle,
    const T* A,
    T* x,
    const int& size,
    const int* devIpiv,
    int* devInfo) { return CUSOLVER_STATUS_INVALID_VALUE; };

template<>
cusolverStatus_t cusolverDngetrs<double>(
    const cusolverDnHandle_t& handle,
    const double* A,
    double* x,
    const int& size,
    const int* devIpiv,
    int* devInfo);

template<>
cusolverStatus_t cusolverDngetrs<float>(
    const cusolverDnHandle_t& handle,
    const float* A,
    float* x,
    const int& size,
    const int* devIpiv,
    int* devInfo);

// solve A*x = b by LU with partial pivoting
template<typename T>
int linearSolverLU(
    const cusolverDnHandle_t& handle,
    const T* const Acopy,
    const T* const b,
    T* const x,
    const int& size);

template<typename T>
T vec_norminf(const T* const x, const int& size) { return (T)0; };
template<>
double vec_norminf<double>(const double* const x, const int& size);
template<>
float vec_norminf<float>(const float* const x, const int& size);

// |A| = max { |A|*ones(m,1) }
template<typename T>
T mat_norminf(const T* const A, const int& size) { return (T)0; };
template<>
double mat_norminf<double>(const double* const A, const int& size);
template<>
float mat_norminf<float>(const float* const A, const int& size);

#endif  // MAIN_H
