#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

namespace open3d
{
    static const float FLT_THRESHOLD = -1e3;
    static const float FLT_PRECISION = 3;
    static const float FLT_WIDTH = 8;

    static const float DBL_THRESHOLD = -1e6;
    static const float DBL_PRECISION = 6;
    static const float DBL_WIDTH = 12;

    template<typename T>
    struct Vector3
    {
        typedef union alignas(4 * sizeof(T)) _Type
        {
            // data
            struct { T x, y, z; };
            struct { T r, g, b; };

            // subscript operator: readwrite
            T& operator [](const int& i);
            // subscript operator: readonly
            const T& operator [](const int& i) const;

            // casting operator: readwrite
            explicit operator T* const();
            // casting operator: readonly
            explicit operator const T* const();

            bool operator ==(const _Type& v) const;
            bool operator !=(const _Type& v) const;
            bool operator <=(const _Type& v) const;
            bool operator >=(const _Type& v) const;

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

            // Less than or equal X component.
            // Comparator for use with std::sort.
            static bool LEX(const _Type& v0, const _Type& v1);
            // Greater than or equal X component.
            // Comparator for use with std::sort.
            static bool GEX(const _Type& v0, const _Type& v1);
            // Less than or equal Y component.
            // Comparator for use with std::sort.
            static bool LEY(const _Type& v0, const _Type& v1);
            // Greater than or equal Y component.
            // Comparator for use with std::sort.
            static bool GEY(const _Type& v0, const _Type& v1);
            // Less than or equal Z component.
            // Comparator for use with std::sort.
            static bool LEZ(const _Type& v0, const _Type& v1);
            // Greater than or equal Z component.
            // Comparator for use with std::sort.
            static bool GEZ(const _Type& v0, const _Type& v1);
        } Type;
    };

    typedef Vector3<double>::Type Vector3d;
    typedef Vector3<float>::Type Vector3f;
    typedef Vector3<int>::Type Vector3i;

    // Display.
    std::ostream& operator <<(std::ostream& os, const Vector3d& v);
    std::ostream& operator <<(std::ostream& os, const Vector3f& v);
    std::ostream& operator <<(std::ostream& os, const Vector3i& v);
}