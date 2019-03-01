#pragma once

#include <cassert>
#include <cmath>

namespace open3d
{
    template<typename T>
    struct Vector3
    {
        typedef union alignas(4 * sizeof(T))
        {
            // data
            struct { T x, y, z; };
            struct { T r, g, b; };
            T s[];

            T& operator [](const int& i);
            const T& operator [](const int& i) const;
            operator T* const();
            operator const T* const();
        } Type;
    };

    extern "C"
    {
        typedef Vector3<int>::Type Vector3i;
        typedef Vector3<float>::Type Vector3f;
        typedef Vector3<double>::Type Vector3d;
    }
}
