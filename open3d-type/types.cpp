
#include <cassert>
#include <cmath>

#include "types.h"

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T>
T& open3d::Vector3<T>::Type::operator [](const int& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    switch(i)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    };
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T>
const T& open3d::Vector3<T>::Type::operator [](const int& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    switch(i)
    {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    };
}

// ----------------------------------------------------------------------------
// casting operator: readwrite
// ----------------------------------------------------------------------------
template<typename T>
open3d::Vector3<T>::Type::operator T* const()
{
    return reinterpret_cast<T*>(this);
}

// ----------------------------------------------------------------------------
// casting operator: readonly
// ----------------------------------------------------------------------------
template<typename T>
open3d::Vector3<T>::Type::operator const T* const()
{
    return reinterpret_cast<T*>(this);
}

// int
template int& open3d::Vector3<int>::Type::operator [](const int& i);
template const int& open3d::Vector3<int>::Type::operator [](const int& i) const;
template open3d::Vector3<int>::Type::operator int* const();
template open3d::Vector3<int>::Type::operator const int* const();

// float
template float& open3d::Vector3<float>::Type::operator [](const int& i);
template const float& open3d::Vector3<float>::Type::operator [](const int& i) const;
template open3d::Vector3<float>::Type::operator float* const();
template open3d::Vector3<float>::Type::operator const float* const();

// double
template double& open3d::Vector3<double>::Type::operator [](const int& i);
template const double& open3d::Vector3<double>::Type::operator [](const int& i) const;
template open3d::Vector3<double>::Type::operator double* const();
template open3d::Vector3<double>::Type::operator const double* const();
