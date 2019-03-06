
#include <cassert>
#include <cmath>

#include "Matrix.h"

#include <iomanip>
using namespace std;

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
T* open3d::Matrix<T, R, C>::Type::operator [](const uint& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return (T*)&s[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
const T* open3d::Matrix<T, R, C>::Type::operator [](const uint& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return (const T* const)&s[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T, uint R>
T& open3d::Matrix<T, R, 1>::Type::operator [](const uint& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return s[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T, uint R>
const T& open3d::Matrix<T, R, 1>::Type::operator [](const uint& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return s[i];
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
bool open3d::Matrix<T, R, C>::Type::operator ==(const open3d::Matrix<T, R, C>::Type& m)
{
    for (uint r = 0; r < R; r++)
        for (uint c = 0; c < C; c++)
            if ((*this)[r][c] != m[r][c])
                return false;

    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
bool open3d::Matrix<T, R, C>::Type::operator !=(const open3d::Matrix<T, R, C>::Type& m)
{
    return !(*this == m);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
bool open3d::Matrix<T, R, C>::Type::operator <=(const open3d::Matrix<T, R, C>::Type& m)
{
    for (uint r = 0; r < R; r++)
        for (uint c = 0; c < C; c++)
            if ((*this)[r][c] > m[r][c])
                return false;

    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
bool open3d::Matrix<T, R, C>::Type::operator >=(const open3d::Matrix<T, R, C>::Type& m)
{
    for (uint r = 0; r < R; r++)
        if ((*this)[r] < m[r])
            return false;

    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R>
bool open3d::Matrix<T, R, 1>::Type::operator ==(const open3d::Matrix<T, R, 1>::Type& m)
{
    for (uint r = 0; r < R; r++)
        if ((*this)[r] != m[r])
            return false;

    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R>
bool open3d::Matrix<T, R, 1>::Type::operator !=(const open3d::Matrix<T, R, 1>::Type& m)
{
    return !(*this == m);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R>
bool open3d::Matrix<T, R, 1>::Type::operator <=(const open3d::Matrix<T, R, 1>::Type& m)
{
    for (uint r = 0; r < R; r++)
        if ((*this)[r] > m[r])
            return false;

    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template<typename T, uint R>
bool open3d::Matrix<T, R, 1>::Type::operator >=(const open3d::Matrix<T, R, 1>::Type& m)
{
    for (uint r = 0; r < R; r++)
        if ((*this)[r] < m[r])
            return false;

    return true;
}

// Template instantiations:
template class open3d::Matrix<float, 3, 3>;
template class open3d::Matrix<float, 3, 1>;
