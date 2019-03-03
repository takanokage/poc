#pragma once

#include <cassert>
#include <cmath>

namespace open3d
{
    extern "C"
    {
    typedef union alignas(4 * sizeof(float)) _Vector3f
    {
        // data
        struct { float x, y, z; };
        struct { float r, g, b; };

        float& operator [](const int& i);
        const float& operator [](const int& i) const;
        operator float* const();
        operator const float* const();
        bool operator ==(const _Vector3f& v) const;
        bool operator !=(const _Vector3f& v) const;
    } Vector3f;
    }
}
