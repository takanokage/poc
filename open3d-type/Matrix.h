#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

typedef unsigned int uint;

namespace open3d
{
    template<typename T, uint R, uint C>
    struct Matrix
    {
        typedef struct _Type
        {
            T s[R][C];

            // subscript operator: readwrite
            T* operator [](const uint& i);
            // subscript operator: readonly
            const T* operator [](const uint& i) const;
        } Type;
    };
    template<typename T, uint R>
    struct Matrix<T, R, 1>
    {
        typedef struct _Type
        {
            T s[R];

            // subscript operator: readwrite
            T& operator [](const uint& i);
            // subscript operator: readonly
            const T& operator [](const uint& i) const;
        } Type;
    };

    template<typename T, uint R>
    using Vector = typename Matrix<T, R, 1>::Type;

    template<typename T>
    using Vector3 = typename Matrix<T, 3, 1>::Type;

    typedef Matrix<float, 3, 3>::Type Matrix3f;
    typedef Matrix<float, 3, 1>::Type Vector3f;
}
