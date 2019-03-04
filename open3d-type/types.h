#pragma once

#include <cassert>
#include <cmath>

#include <iostream>

extern "C"
{
    namespace open3d
    {
        namespace DIM
        {
            typedef enum _Type
            {
                X = 0,
                Y = 1,
                Z = 2,
                W = 3
            } Type;
        };

        static const float FLT_PRECISION = 6;
        static const float FLT_WIDTH = 14;

        typedef union alignas(4 * sizeof(float)) _Vector3f
        {
            // data
            struct { float x, y, z; };
            struct { float r, g, b; };

            // subscript operator: readwrite
            float& operator [](const int& i);
            // subscript operator: readonly
            const float& operator [](const int& i) const;

            // casting operator: readwrite
            explicit operator float* const();
            // casting operator: readonly
            explicit operator const float* const();

            bool operator ==(const _Vector3f& v) const;
            bool operator !=(const _Vector3f& v) const;
            bool operator <=(const _Vector3f& v) const;
            bool operator >=(const _Vector3f& v) const;

            // addition
            _Vector3f operator +(const _Vector3f& v) const;
            // subtraction
            _Vector3f operator -(const _Vector3f& v) const;
            // addition
            _Vector3f& operator +=(const _Vector3f& v);
            // subtraction
            _Vector3f& operator -=(const _Vector3f& v);
            // addition
            _Vector3f operator +(const float& v) const;
            // subtraction
            _Vector3f operator -(const float& v) const;
            // multiply with scalar
            _Vector3f operator *(const float& v) const;
            // divide by scalar
            _Vector3f operator /(const float& v) const;
            // addition
            _Vector3f& operator +=(const float& v);
            // subtraction
            _Vector3f& operator -=(const float& v);
            // multiply with scalar
            _Vector3f& operator *=(const float& v);
            // divide by scalar
            _Vector3f& operator /=(const float& v);

            // Less than or equal X component.
            // Comparator for use with std::sort.
            static bool LEX(const _Vector3f& v0, const _Vector3f& v1);
            // Greater than or equal X component.
            // Comparator for use with std::sort.
            static bool GEX(const _Vector3f& v0, const _Vector3f& v1);
            // Less than or equal Y component.
            // Comparator for use with std::sort.
            static bool LEY(const _Vector3f& v0, const _Vector3f& v1);
            // Greater than or equal Y component.
            // Comparator for use with std::sort.
            static bool GEY(const _Vector3f& v0, const _Vector3f& v1);
            // Less than or equal Z component.
            // Comparator for use with std::sort.
            static bool LEZ(const _Vector3f& v0, const _Vector3f& v1);
            // Greater than or equal Z component.
            // Comparator for use with std::sort.
            static bool GEZ(const _Vector3f& v0, const _Vector3f& v1);

            // friend operators
            friend std::ostream& operator <<(std::ostream& os, const _Vector3f& v);
        } Vector3f;

        // Display an open3d::Vector3f.
        std::ostream& operator <<(std::ostream& os, const Vector3f& v);
    }
}
