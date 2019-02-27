// based on the NVIDIA_CUDA-10.0_Samples/7_CUDALibraries/cuSolverDn_LinearSolver sample.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include <cuda_runtime.h>

#include "cusparse.h"
#include "performance.h"
#include "main.h"
#include "args.h"

#include <iostream>
using namespace std;

int main (int argc, char * argv[])
{
    Args::Type args = Args::Interpret(argc, argv);

    if (args.sp || args.dp)
        DeviceInfo(args.devID);

    if (args.dp)
        testLU<double>(args.devID, args.size);

    if (args.sp)
        testLU<float>(args.devID, args.size);

    return 0;
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
void DeviceInfo(const int& devID)
{
    cudaDeviceProp deviceProp;

    cudaSetDevice(devID);
    cudaGetDeviceProperties(&deviceProp, devID);

    cout << "GPU Device " << devID << ": ";
    cout << deviceProp.name << ", ";
    cout << "CUDA ";
    cout << deviceProp.major << ".";
    cout << deviceProp.minor << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
// solve a dense A*x=b exquation using cuSolver/LU.
// size = rows = cols, A is a square matrix
// ----------------------------------------------------------------------------
template<typename T>
void testLU(const int& devID, const int& size)
{
    cudaSetDevice(devID);

    cusolverDnHandle_t handle = NULL;
    cublasHandle_t cublasHandle = NULL; // used in residual evaluation

    // host memory
    T* h_A = NULL;
    T* h_x = NULL;
    T* h_b = NULL;
    T* h_r = NULL; // r = b - A * x

    // device memory
    T* d_A = NULL;
    T* d_x = NULL;
    T* d_b = NULL;
    T* d_r = NULL; // r = b - A * x

    T x_inf = 0.0;
    T r_inf = 0.0;
    T A_inf = 0.0;
    int errors = 0;

    h_A = (T*)malloc(sizeof(T) * size * size);
    h_x = (T*)malloc(sizeof(T) * size);
    h_b = (T*)malloc(sizeof(T) * size);
    h_r = (T*)malloc(sizeof(T) * size);
    assert(NULL != h_A);
    assert(NULL != h_x);
    assert(NULL != h_b);
    assert(NULL != h_r);

    memset(h_A, 0, sizeof(T) * size * size);

    // initialize A & b on host.
    for (int i = 1; i < size *  size; i++)
        h_A[i] = (float)rand() / RAND_MAX;

    for(int i = 0 ; i < size ; i++)
        h_b[i] = (float)rand() / RAND_MAX;

    cusolverDnCreate(&handle);
    cublasCreate(&cublasHandle);

    // allocate device memory
    cudaMalloc((void**)&d_A, sizeof(T) * size * size);
    cudaMalloc((void**)&d_x, sizeof(T) * size);
    cudaMalloc((void**)&d_b, sizeof(T) * size);
    cudaMalloc((void**)&d_r, sizeof(T) * size);

    // copy host data to the device
    cudaMemcpy(d_A, h_A, sizeof(T) * size * size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(T) * size, cudaMemcpyHostToDevice);

    // solve A * x = b
    // d_A and d_b are read-only
    linearSolverLU(handle, d_A, d_b, d_x, size);

    // evaluate residual
    cudaMemcpy(d_r, d_b, sizeof(T) * size, cudaMemcpyDeviceToDevice);

    // r = b - A * x
    Residual<T>(cublasHandle, d_A, d_x, d_r, size);

    cudaMemcpy(h_x, d_x, sizeof(T) * size, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_r, d_r, sizeof(T) * size, cudaMemcpyDeviceToHost);

    x_inf = vec_norminf(h_x, size);
    r_inf = vec_norminf(h_r, size);
    A_inf = mat_norminf(h_A, size);

    printf("|b - A * x| = %E\n", r_inf);
    printf("|A| = %E\n", A_inf);
    printf("|x| = %E\n", x_inf);
    printf("|b - A * x|/(|A| * |x|) = %E\n\n", r_inf/(A_inf *  x_inf));

    if (handle) { cusolverDnDestroy(handle); }
    if (cublasHandle) { cublasDestroy(cublasHandle); }

    if (h_A) { free(h_A); }
    if (h_x) { free(h_x); }
    if (h_b) { free(h_b); }
    if (h_r) { free(h_r); }

    if (d_A) { cudaFree(d_A); }
    if (d_x) { cudaFree(d_x); }
    if (d_b) { cudaFree(d_b); }
    if (d_r) { cudaFree(d_r); }
}

// ----------------------------------------------------------------------------
// double precision
// ----------------------------------------------------------------------------
template<>
void Residual<double>(
    const cublasHandle_t& cublasHandle,
    double* d_A,
    double* d_x,
    double* d_r,
    const int& size)
{
    // the constants are used in residual evaluation, r = b - A * x
    const double minus_one = -1.0;
    const double one = 1.0;

    cublasDgemm_v2(cublasHandle, CUBLAS_OP_N, CUBLAS_OP_N,
                   size, 1, size, &minus_one,
                   d_A, size, d_x, size,
                   &one, d_r, size);
}

// ----------------------------------------------------------------------------
// single precision
// ----------------------------------------------------------------------------
template<>
void Residual<float>(
    const cublasHandle_t& cublasHandle,
    float* d_A,
    float* d_x,
    float* d_r,
    const int& size)
{
    // the constants are used in residual evaluation, r = b - A * x
    const float minus_one = -1.0;
    const float one = 1.0;

    cublasSgemm_v2(cublasHandle, CUBLAS_OP_N, CUBLAS_OP_N,
                   size, 1, size, &minus_one,
                   d_A, size, d_x, size,
                   &one, d_r, size);
}

// ----------------------------------------------------------------------------
// Calculate the size of work buffers needed in double precision.
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrf_bufferSize<double>(
    const cusolverDnHandle_t& handle,
    const double* const A,
    const int& size,
    int* Lwork)
{
    return cusolverDnDgetrf_bufferSize(handle, size, size, (double*)A, size, Lwork);
}

// ----------------------------------------------------------------------------
// Calculate the size of work buffers needed in single precision.
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrf_bufferSize<float>(
    const cusolverDnHandle_t& handle,
    const float* const A,
    const int& size,
    int* Lwork)
{
    return cusolverDnSgetrf_bufferSize(handle, size, size, (float*)A, size, Lwork);
}

// ----------------------------------------------------------------------------
// compute the LU factorization of a n×n matrix in double precision.
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrf<double>(
    const cusolverDnHandle_t& handle,
    double* A,
    const int& size,
    double* Workspace,
    int *devIpiv,
    int *devInfo)
{
    cusolverDnDgetrf(handle, size, size, A, size, Workspace, devIpiv, devInfo);
}

// ----------------------------------------------------------------------------
// compute the LU factorization of a n×n matrix in single precision.
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrf<float>(
    const cusolverDnHandle_t& handle,
    float* A,
    const int& size,
    float* Workspace,
    int *devIpiv,
    int *devInfo)
{
    cusolverDnSgetrf(handle, size, size, A, size, Workspace, devIpiv, devInfo);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrs<double>(
    const cusolverDnHandle_t& handle,
    const double* A,
    double* x,
    const int& size,
    const int* devIpiv,
    int* devInfo)
{
    cusolverDnDgetrs(handle, CUBLAS_OP_N, size, 1, A, size, devIpiv, x, size, devInfo);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
template<>
cusolverStatus_t cusolverDngetrs<float>(
    const cusolverDnHandle_t& handle,
    const float* A,
    float* x,
    const int& size,
    const int* devIpiv,
    int* devInfo)
{
    cusolverDnSgetrs(handle, CUBLAS_OP_N, size, 1, A, size, devIpiv, x, size, devInfo);
}

// ----------------------------------------------------------------------------
// solve A*x = b by LU with partial pivoting
// ----------------------------------------------------------------------------
template<typename T>
int linearSolverLU(
    const cusolverDnHandle_t& handle,
    const T* const Acopy,
    const T* const b,
    T* const x,
    const int& size)
{
    int bufferSize = 0;
    int* info = NULL;
    T* buffer = NULL;
    T* A = NULL;
    int* ipiv = NULL; // pivoting sequence
    int h_info = 0;

    cusolverDngetrf_bufferSize(handle, Acopy, size, &bufferSize);

    cudaMalloc(&info, sizeof(int));
    cudaMalloc(&buffer, sizeof(T) * bufferSize);
    cudaMalloc(&A, sizeof(T) * size * size);
    cudaMalloc(&ipiv, sizeof(int) * size);

    // prepare a copy of A because getrf will overwrite A with L
    cudaMemcpy(A, Acopy, sizeof(T) * size * size, cudaMemcpyDeviceToDevice);
    cudaMemset(info, 0, sizeof(int));

    Performance::Start();

    cusolverDngetrf(handle, A, size, buffer, ipiv, info);

    cudaMemcpy(&h_info, info, sizeof(int), cudaMemcpyDeviceToHost);

    if ( 0 != h_info ){
        fprintf(stderr, "Error: LU factorization failed\n");
    }

    cudaMemcpy(x, b, sizeof(T) * size, cudaMemcpyDeviceToDevice);

    cusolverDngetrs(handle, A, x, size, ipiv, info);

    cudaDeviceSynchronize();
    Performance::Stop();

    fprintf (stdout, "timing: LU = %g ms\n", Performance::Duration());

    if (info  ) { cudaFree(info  ); }
    if (buffer) { cudaFree(buffer); }
    if (A     ) { cudaFree(A); }
    if (ipiv  ) { cudaFree(ipiv);}

    return 0;
}

// ----------------------------------------------------------------------------
// double precision
// ----------------------------------------------------------------------------
template<>
double vec_norminf<double>(const double* const x, const int& size)
{
    double norminf = 0;
    for(int j = 0 ; j < size ; j++)
    {
        double x_abs = fabs(x[j]);
        norminf = (norminf > x_abs)? norminf : x_abs;
    }

    return norminf;
}

// ----------------------------------------------------------------------------
// single precision
// ----------------------------------------------------------------------------
template<>
float vec_norminf<float>(const float* const x, const int& size)
{
    float norminf = 0;
    for(int j = 0 ; j < size ; j++)
    {
        float x_abs = fabsf(x[j]);
        norminf = (norminf > x_abs)? norminf : x_abs;
    }

    return norminf;
}

// ----------------------------------------------------------------------------
// |A| = max { |A|*ones(m,1) }
// double precision
// ----------------------------------------------------------------------------
template<>
double mat_norminf<double>(const double* const A, const int& size)
{
    double norminf = 0;
    for(int i = 0 ; i < size ; i++)
    {
        double sum = 0.0;
        for(int j = 0 ; j < size ; j++)
        {
           double A_abs = fabs(A[i + j * size]);
           sum += A_abs;
        }

        norminf = (norminf > sum)? norminf : sum;
    }

    return norminf;
}

// ----------------------------------------------------------------------------
// |A| = max { |A|*ones(m,1) }
// single precision
// ----------------------------------------------------------------------------
template<>
float mat_norminf(const float* const A, const int& size)
{
    float norminf = 0;
    for(int i = 0 ; i < size ; i++)
    {
        float sum = 0.0;
        for(int j = 0 ; j < size ; j++)
        {
           float A_abs = fabsf(A[i + j * size]);
           sum += A_abs;
        }

        norminf = (norminf > sum)? norminf : sum;
    }

    return norminf;
}
