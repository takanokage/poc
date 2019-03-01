#pragma once

#include <cassert>
#include <cmath>

namespace open3d
{
    template<typename T>
    struct Vector3
    {
        typedef union alignas(4 * sizeof(T)) _Type
        {
            // data
            struct { T x, y, z; };
            struct { T r, g, b; };
            T s[];

            // subscript operator: readwrite
            T& operator [](const int& i)
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

            // subscript operator: readonly
            const T& operator [](const int& i) const
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

            // casting operator: readwrite
            operator T* const()
            {
                return reinterpret_cast<T*>(this);
            }

            // casting operator: readonly
            operator const T* const()
            {
                return reinterpret_cast<T*>(this);
            }
        } Type;
    };

    extern "C"
    {
        typedef Vector3<int>::Type Vector3i;
        typedef Vector3<float>::Type Vector3f;
        typedef Vector3<double>::Type Vector3d;
    }
}
