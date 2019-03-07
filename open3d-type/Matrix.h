#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

typedef unsigned int uint;

// smallest power of two strictly greater than n
template <uint N>
struct pow2g { enum { value = (pow2g<(N >> 1)>::value) << 1 }; };
template <>
struct pow2g<0> { enum { value = 1 }; };

// smallest power of two greater than or equal to n
template <uint N> struct pow2ge {
	enum {
        value = (pow2g<(N >> 1)>::value == N) ? N : ((pow2g<(N >> 1)>::value) << 1)
    };
};
template <> struct pow2ge<0> { enum { value = 1 }; };

namespace open3d
{
    // 2D tensor, row major
    template<typename T, uint ROWS, uint COLS>
    struct Matrix
    {
        typedef struct alignas(pow2ge<ROWS * COLS * sizeof(T)>::value) _Type
        {
            T s[ROWS][COLS];

            // subscript operator: readwrite
            T* operator [](const uint& i);
            // subscript operator: readonly
            const T* operator [](const uint& i) const;

            // casting operator: readwrite
            explicit operator T* const();
            // casting operator: readonly
            explicit operator const T* const();

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
        typedef struct alignas(pow2ge<COLS * sizeof(T)>::value) _Type
        {
            T s[COLS];

            // subscript operator: readwrite
            T& operator [](const uint& i);
            // subscript operator: readonly
            const T& operator [](const uint& i) const;

            // casting operator: readwrite
            explicit operator T* const();
            // casting operator: readonly
            explicit operator const T* const();

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

    // 2D tensor, row major, size 3
    template<typename T>
    using Matrix3 = typename Matrix<T, 3, 3>::Type;

    // 1D tensor, row major, unspecified number of elements
    template<typename T, uint COLS>
    using Vector = typename Matrix<T, 1, COLS>::Type;

    // 1D tensor, row major, size 3
    template<typename T>
    using Vector3 = typename Matrix<T, 1, 3>::Type;

    // 2D 3x3 tensor
    // typedef Matrix<float, 3, 3>::Type Matrix3f;
    typedef Matrix3<float> Matrix3f;
    // 1D 1x3 tensor
    // typedef Vector<float, 3> Vector3f;
    typedef Vector3<float> Vector3f;
}
