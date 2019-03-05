#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

namespace open3d
{
    template<typename T, int R, int C>
    struct Matrix
    {
        /*/// v0
        typedef union _Type
        {
            T s[R][C];
        } Type;
        /*/// v1
        typedef struct _Type
        {
            T s[R][C];
        } Type;
        //*///
    };

    template<typename T, int R>
    using Vector = typename Matrix<T, R, 1>::Type;

    template<typename T>
    using Vector3 = typename Matrix<T, 3, 1>::Type;
}
