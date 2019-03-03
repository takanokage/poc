
#include <cassert>
#include <cmath>

#include "types.h"

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
float& open3d::Vector3f::operator [](const int& i)
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
const float& open3d::Vector3f::operator [](const int& i) const
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
open3d::Vector3f::operator float* const()
{
    return reinterpret_cast<float*>(this);
}

// ----------------------------------------------------------------------------
// casting operator: readonly
// ----------------------------------------------------------------------------
open3d::Vector3f::operator const float* const()
{
    return reinterpret_cast<float*>(this);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool open3d::Vector3f::operator ==(const open3d::Vector3f& v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z);
}
