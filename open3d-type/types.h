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

            // subscript operators
            float& operator [](const int& i);
            const float& operator [](const int& i) const;

            // cast operators
            explicit operator float* const();
            explicit operator const float* const();

            // comparison operators
            bool operator ==(const _Vector3f& v) const;
            bool operator !=(const _Vector3f& v) const;
            bool operator <=(const _Vector3f& v) const;
            bool operator >=(const _Vector3f& v) const;

            // comparators for use with std::sort
            static bool LEX(const _Vector3f& v0, const _Vector3f& v1);
            static bool GEX(const _Vector3f& v0, const _Vector3f& v1);
            static bool LEY(const _Vector3f& v0, const _Vector3f& v1);
            static bool GEY(const _Vector3f& v0, const _Vector3f& v1);
            static bool LEZ(const _Vector3f& v0, const _Vector3f& v1);
            static bool GEZ(const _Vector3f& v0, const _Vector3f& v1);

            // friend operators
            friend std::ostream& operator <<(std::ostream& os, const _Vector3f& v);
        } Vector3f;

        std::ostream& operator <<(std::ostream& os, const Vector3f& v);
    }
}
