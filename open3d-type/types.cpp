
#include <cassert>
#include <cmath>

#include "types.h"

#include <iomanip>
using namespace std;

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
float& open3d::Vector3f::operator [](const int& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((float*)this)[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
const float& open3d::Vector3f::operator [](const int& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((const float* const)this)[i];
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
    return reinterpret_cast<const float* const>(this);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool open3d::Vector3f::operator ==(const open3d::Vector3f& v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool open3d::Vector3f::operator !=(const open3d::Vector3f& v) const
{
    return !(this->operator==(v));
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool open3d::Vector3f::operator <=(const open3d::Vector3f& v) const
{
    return (x <= v.x) && (y <= v.y) && (z <= v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool open3d::Vector3f::operator >=(const open3d::Vector3f& v) const
{
    return (x >= v.x) && (y >= v.y) && (z >= v.z);
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator +(const open3d::Vector3f& v) const
{
    Vector3f output = {x + v.x, y + v.y, z + v.z };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator -(const open3d::Vector3f& v) const
{
    Vector3f output = {x - v.x, y - v.y, z - v.z };

    return output;
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator +=(const open3d::Vector3f& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator -=(const open3d::Vector3f& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator +(const float& v) const
{
    Vector3f output = {x + v, y + v, z + v };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator -(const float& v) const
{
    Vector3f output = {x - v, y - v, z - v };

    return output;
}

// ----------------------------------------------------------------------------
// multiply with scalar.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator *(const float& v) const
{
    Vector3f output = {x * v, y * v, z * v };

    return output;
}

// ----------------------------------------------------------------------------
// divide by scalar.
// ----------------------------------------------------------------------------
open3d::Vector3f open3d::Vector3f::operator /(const float& v) const
{
    Vector3f output = {x / v, y / v, z / v };

    return output;
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator +=(const float& v)
{
    x += v;
    y += v;
    z += v;

    return *this;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator -=(const float& v)
{
    x -= v;
    y -= v;
    z -= v;

    return *this;
}

// ----------------------------------------------------------------------------
// multiply with scalar.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator *=(const float& v)
{
    x *= v;
    y *= v;
    z *= v;

    return *this;
}

// ----------------------------------------------------------------------------
// divide by scalar.
// ----------------------------------------------------------------------------
open3d::Vector3f& open3d::Vector3f::operator /=(const float& v)
{
    x /= v;
    y /= v;
    z /= v;

    return *this;
}

// ----------------------------------------------------------------------------
// Less than or equal X component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::LEX(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.x <= v1.x;
}

// ----------------------------------------------------------------------------
// Greater than or equal X component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::GEX(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.x >= v1.x;
}

// ----------------------------------------------------------------------------
// Less than or equal Y component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::LEY(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.y <= v1.y;
}

// ----------------------------------------------------------------------------
// Greater than or equal Y component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::GEY(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.y >= v1.y;
}

// ----------------------------------------------------------------------------
// Less than or equal Z component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::LEZ(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.z <= v1.z;
}

// ----------------------------------------------------------------------------
// Greater than or equal Z component.
// ----------------------------------------------------------------------------
bool open3d::Vector3f::GEZ(const open3d::Vector3f& v0, const open3d::Vector3f& v1)
{
    return v0.z >= v1.z;
}

// ----------------------------------------------------------------------------
// Display an open3d::Vector3f.
// ----------------------------------------------------------------------------
ostream& open3d::operator <<(ostream& os, const open3d::Vector3f& v)
{
    // save existing precision
    int oldPrecision = cout.precision();

    // set new precision
    cout.precision(FLT_PRECISION);
    cout.setf(ios::fixed);

    cout << setw(FLT_WIDTH) << v[0];
    cout << setw(FLT_WIDTH) << v[1];
    cout << setw(FLT_WIDTH) << v[2];

    // restore
    cout.precision(oldPrecision);
    cout.unsetf(ios::fixed);

    cout.flush();
}
