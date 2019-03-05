
#include <cassert>
#include <cmath>

#include "types.h"

#include <iomanip>
using namespace std;

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T>
T& open3d::Vector3<T>::Type::operator [](const int& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((T*)this)[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T>
const T& open3d::Vector3<T>::Type::operator [](const int& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((const T* const)this)[i];
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
    return reinterpret_cast<const T* const>(this);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator ==(const open3d::Vector3<T>::Type& v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator !=(const open3d::Vector3<T>::Type& v) const
{
    return !(this->operator==(v));
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator <=(const open3d::Vector3<T>::Type& v) const
{
    return (x <= v.x) && (y <= v.y) && (z <= v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator >=(const open3d::Vector3<T>::Type& v) const
{
    return (x >= v.x) && (y >= v.y) && (z >= v.z);
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator +(const open3d::Vector3<T>::Type& v) const
{
    Vector3<T>::Type output = {x + v.x, y + v.y, z + v.z };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator -(const open3d::Vector3<T>::Type& v) const
{
    Vector3<T>::Type output = {x - v.x, y - v.y, z - v.z };

    return output;
}

// ----------------------------------------------------------------------------
// addtion assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator +=(const open3d::Vector3<T>::Type& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

// ----------------------------------------------------------------------------
// subtraction assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator -=(const open3d::Vector3<T>::Type& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator +(const T& v) const
{
    Vector3<T>::Type output = {x + v, y + v, z + v };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator -(const T& v) const
{
    Vector3<T>::Type output = {x - v, y - v, z - v };

    return output;
}

// ----------------------------------------------------------------------------
// multiply with scalar.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator *(const T& v) const
{
    Vector3<T>::Type output = {x * v, y * v, z * v };

    return output;
}

// ----------------------------------------------------------------------------
// divide by scalar.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator /(const T& v) const
{
    Vector3<T>::Type output = {x / v, y / v, z / v };

    return output;
}

// ----------------------------------------------------------------------------
// addtion assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator +=(const T& v)
{
    x += v;
    y += v;
    z += v;

    return *this;
}

// ----------------------------------------------------------------------------
// subtraction assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator -=(const T& v)
{
    x -= v;
    y -= v;
    z -= v;

    return *this;
}

// ----------------------------------------------------------------------------
// multiplication assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator *=(const T& v)
{
    x *= v;
    y *= v;
    z *= v;

    return *this;
}

// ----------------------------------------------------------------------------
// division assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator /=(const T& v)
{
    x /= v;
    y /= v;
    z /= v;

    return *this;
}

// ----------------------------------------------------------------------------
// Less than or equal X component.
// ----------------------------------------------------------------------------
// template<template<typename> typename V, typename T>
// bool LEX(const typename V<T>::Type& v0, const typename V<T>::Type& v1)
// template<template<typename> typename Vector3, typename T>
// bool LEX(const typename open3d::Vector3<T>::Type& v0, const typename open3d::Vector3<T>::Type& v1)
template<typename T>
bool open3d::Vector3<T>::Type::LEX(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.x <= v1.x;
}

// ----------------------------------------------------------------------------
// Greater than or equal X component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEX(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.x >= v1.x;
}

// ----------------------------------------------------------------------------
// Less than or equal Y component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::LEY(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.y <= v1.y;
}

// ----------------------------------------------------------------------------
// Greater than or equal Y component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEY(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.y >= v1.y;
}

// ----------------------------------------------------------------------------
// Less than or equal Z component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::LEZ(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.z <= v1.z;
}

// ----------------------------------------------------------------------------
// Greater than or equal Z component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEZ(const open3d::Vector3<T>::Type& v0, const open3d::Vector3<T>::Type& v1)
{
    return v0.z >= v1.z;
}

// ----------------------------------------------------------------------------
// Display an open3d::Vector3<T>::Type.
// ----------------------------------------------------------------------------
ostream& open3d::operator <<(ostream& os, const open3d::Vector3f& v)
{
    // save
    ios_base::fmtflags flags = cout.flags();

    // set new precision
    cout.precision(FLT_PRECISION);
    cout.setf(ios::fixed);

    cout << setw(FLT_WIDTH) << v.x;
    cout << setw(FLT_WIDTH) << v.y;
    cout << setw(FLT_WIDTH) << v.z;

    // restore
    cout.flags(flags);

    cout.flush();
}

// Template instantiations:
template class open3d::Vector3<double>;
template class open3d::Vector3<float>;
template class open3d::Vector3<int>;
