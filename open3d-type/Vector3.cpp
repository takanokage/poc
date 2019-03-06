
#include <cassert>
#include <cmath>

#include "Vector3.h"

#include <iomanip>
using namespace std;

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T>
T& open3d::Vector3<T>::Type::operator [](const uint& i)
{
    // catch error in debug mode
    assert(i < 3);

    return ((T*)this)[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T>
const T& open3d::Vector3<T>::Type::operator [](const uint& i) const
{
    // catch error in debug mode
    assert(i < 3);

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
bool open3d::Vector3<T>::Type::operator ==(
    const open3d::Vector3<T>::Type& v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator !=(
    const open3d::Vector3<T>::Type& v) const
{
    return !(this->operator==(v));
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator <=(
    const open3d::Vector3<T>::Type& v) const
{
    return (x <= v.x) && (y <= v.y) && (z <= v.z);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::operator >=(
    const open3d::Vector3<T>::Type& v) const
{
    return (x >= v.x) && (y >= v.y) && (z >= v.z);
}

// ----------------------------------------------------------------------------
// addtion.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator +(
    const open3d::Vector3<T>::Type& v) const
{
    Vector3<T>::Type output = {x + v.x, y + v.y, z + v.z };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator -(
    const open3d::Vector3<T>::Type& v) const
{
    Vector3<T>::Type output = {x - v.x, y - v.y, z - v.z };

    return output;
}

// ----------------------------------------------------------------------------
// addtion assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator +=(
    const open3d::Vector3<T>::Type& v)
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
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator -=(
    const open3d::Vector3<T>::Type& v)
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
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator +(
    const T& t) const
{
    Vector3<T>::Type output = {x + t, y + t, z + t };

    return output;
}

// ----------------------------------------------------------------------------
// subtraction.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator -(
    const T& t) const
{
    Vector3<T>::Type output = {x - t, y - t, z - t };

    return output;
}

// ----------------------------------------------------------------------------
// multiply with scalar.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator *(
    const T& t) const
{
    Vector3<T>::Type output = {x * t, y * t, z * t };

    return output;
}

// ----------------------------------------------------------------------------
// divide by scalar.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type open3d::Vector3<T>::Type::operator /(
    const T& t) const
{
    Vector3<T>::Type output = {x / t, y / t, z / t };

    return output;
}

// ----------------------------------------------------------------------------
// addtion assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator +=(
    const T& t)
{
    x += t;
    y += t;
    z += t;

    return *this;
}

// ----------------------------------------------------------------------------
// subtraction assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator -=(
    const T& t)
{
    x -= t;
    y -= t;
    z -= t;

    return *this;
}

// ----------------------------------------------------------------------------
// multiplication assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator *=(
    const T& t)
{
    x *= t;
    y *= t;
    z *= t;

    return *this;
}

// ----------------------------------------------------------------------------
// division assignment.
// ----------------------------------------------------------------------------
template<typename T>
typename open3d::Vector3<T>::Type& open3d::Vector3<T>::Type::operator /=(
    const T& t)
{
    x /= t;
    y /= t;
    z /= t;

    return *this;
}

// ----------------------------------------------------------------------------
// Less than or equal X component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::LEX(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.x <= v1.x;
}

// ----------------------------------------------------------------------------
// Greater than or equal X component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEX(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.x >= v1.x;
}

// ----------------------------------------------------------------------------
// Less than or equal Y component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::LEY(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.y <= v1.y;
}

// ----------------------------------------------------------------------------
// Greater than or equal Y component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEY(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.y >= v1.y;
}

// ----------------------------------------------------------------------------
// Less than or equal Z component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::LEZ(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.z <= v1.z;
}

// ----------------------------------------------------------------------------
// Greater than or equal Z component.
// ----------------------------------------------------------------------------
template<typename T>
bool open3d::Vector3<T>::Type::GEZ(
    const open3d::Vector3<T>::Type& v0,
    const open3d::Vector3<T>::Type& v1)
{
    return v0.z >= v1.z;
}

// ----------------------------------------------------------------------------
// Display an open3d::Vector3<T>::Type.
// ----------------------------------------------------------------------------
ostream& open3d::operator <<(ostream& os, const open3d::Vector3d& v)
{
    // save
    ios_base::fmtflags flags = cout.flags();

    // set new precision
    cout.precision(DBL_PRECISION);
    cout.setf(ios::fixed);

    cout << setw(DBL_WIDTH) << v.x;
    cout << setw(DBL_WIDTH) << v.y;
    cout << setw(DBL_WIDTH) << v.z;

    // restore
    cout.flags(flags);

    cout.flush();
}
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
ostream& open3d::operator <<(ostream& os, const open3d::Vector3i& v)
{
    cout << setw(FLT_WIDTH) << v.x;
    cout << setw(FLT_WIDTH) << v.y;
    cout << setw(FLT_WIDTH) << v.z;

    cout.flush();
}

// Template instantiations:
template class open3d::Vector3<double>;
template class open3d::Vector3<float>;
template class open3d::Vector3<int>;
