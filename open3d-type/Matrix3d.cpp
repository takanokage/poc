
#include "Matrix3d.h"

double *open3d::Matrix3d::operator[](const uint &i) {
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return (double *)&s[i];
}

const double *open3d::Matrix3d::operator[](const uint &i) const {
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return (const double *const) & s[i];
}

open3d::Matrix3d::operator double *const() {
    return reinterpret_cast<double *>(s);
}

open3d::Matrix3d::operator const double *const() {
    return reinterpret_cast<const double *const>(s);
}

bool open3d::Matrix3d::operator==(const typename open3d::Matrix3d &m) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            if ((*this)[r][c] != m[r][c]) return false;

    return true;
}

bool open3d::Matrix3d::operator!=(const typename open3d::Matrix3d &m) {
    return !(*this == m);
}

bool open3d::Matrix3d::operator<=(const typename open3d::Matrix3d &m) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            if ((*this)[r][c] > m[r][c]) return false;

    return true;
}

bool open3d::Matrix3d::operator>=(const typename open3d::Matrix3d &m) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        if ((*this)[r] < m[r]) return false;

    return true;
}

typename open3d::Matrix3d open3d::Matrix3d::operator+(
        const typename open3d::Matrix3d &m) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] + m[r][c];

    return output;
}

typename open3d::Matrix3d open3d::Matrix3d::operator-(
        const typename open3d::Matrix3d &m) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] - m[r][c];

    return output;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator+=(
        const typename open3d::Matrix3d &m) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] += m[r][c];

    return *this;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator-=(
        const typename open3d::Matrix3d &m) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] -= m[r][c];

    return *this;
}

typename open3d::Matrix3d open3d::Matrix3d::operator+(const double &t) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] + t;

    return output;
}

typename open3d::Matrix3d open3d::Matrix3d::operator-(const double &t) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] - t;

    return output;
}

typename open3d::Matrix3d open3d::Matrix3d::operator*(const double &t) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] * t;

    return output;
}

typename open3d::Matrix3d open3d::Matrix3d::operator/(const double &t) const {
    Matrix3d output;
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++)
            output[r][c] = (*this)[r][c] / t;

    return output;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator+=(const double &t) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] += t;

    return *this;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator-=(const double &t) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] -= t;

    return *this;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator*=(const double &t) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] *= t;

    return *this;
}

typename open3d::Matrix3d &open3d::Matrix3d::operator/=(const double &t) {
    for (uint r = 0; r < Matrix3d::ROWS; r++)
        for (uint c = 0; c < Matrix3d::COLS; c++) (*this)[r][c] /= t;

    return *this;
}
