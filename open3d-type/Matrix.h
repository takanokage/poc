#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

typedef unsigned int uint;

namespace open3d
{
    // 2D tensor, row major
    template<typename T, uint ROWS, uint COLS>
    struct Matrix
    {
        typedef struct _Type
        {
            T s[ROWS][COLS];

            // subscript operator: readwrite
            T* operator [](const uint& i);
            // subscript operator: readonly
            const T* operator [](const uint& i) const;

            bool operator ==(const _Type& m);
            bool operator !=(const _Type& m);
            bool operator <=(const _Type& m);
            bool operator >=(const _Type& m);

            // addition
            _Type operator +(const _Type& v) const;
            // subtraction
            _Type operator -(const _Type& v) const;
            // addition assignment
            _Type& operator +=(const _Type& v);
            // subtraction assignment
            _Type& operator -=(const _Type& v);
            // addition
            _Type operator +(const T& v) const;
            // subtraction
            _Type operator -(const T& v) const;
            // multiply with scalar
            _Type operator *(const T& v) const;
            // divide by scalar
            _Type operator /(const T& v) const;
            // addition assignment
            _Type& operator +=(const T& v);
            // subtraction assignment
            _Type& operator -=(const T& v);
            // multiplication assignment
            _Type& operator *=(const T& v);
            // division assignment
            _Type& operator /=(const T& v);
        } Type;
    };

    // 1D tensor, row major
    template<typename T, uint COLS>
    struct Matrix<T, 1, COLS>
    {
        typedef struct _Type
        {
            T s[COLS];

            // subscript operator: readwrite
            T& operator [](const uint& i);
            // subscript operator: readonly
            const T& operator [](const uint& i) const;

            bool operator ==(const _Type& m);
            bool operator !=(const _Type& m);
            bool operator <=(const _Type& m);
            bool operator >=(const _Type& m);

            // addition
            _Type operator +(const _Type& v) const;
            // subtraction
            _Type operator -(const _Type& v) const;
            // addition assignment
            _Type& operator +=(const _Type& v);
            // subtraction assignment
            _Type& operator -=(const _Type& v);
            // addition
            _Type operator +(const T& v) const;
            // subtraction
            _Type operator -(const T& v) const;
            // multiply with scalar
            _Type operator *(const T& v) const;
            // divide by scalar
            _Type operator /(const T& v) const;
            // addition assignment
            _Type& operator +=(const T& v);
            // subtraction assignment
            _Type& operator -=(const T& v);
            // multiplication assignment
            _Type& operator *=(const T& v);
            // division assignment
            _Type& operator /=(const T& v);
        } Type;
    };

    // 1D tensor, row major, unspecified number of elements
    template<typename T, uint COLS>
    using Vector = typename Matrix<T, 1, COLS>::Type;

    // 1D tensor, row major, size 3
    template<typename T>
    using Vector3 = typename Matrix<T, 1, 3>::Type;

    // 2D 3x3 tensor
    typedef Matrix<float, 3, 3>::Type Matrix3f;
    // 1D 1x3 tensor
    typedef Matrix<float, 1, 3>::Type Vector3f;
}
