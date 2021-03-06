
#include "Matrix3f.h"

#include "Matrix3d.h"
#include "Matrix4d.h"
#include "Matrix6d.h"

#include "Vector3f.h"
#include "Vector3d.h"
using namespace open3d;

#include "types.h"
using namespace open3d::DIM;

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "performance.h"

const int width = 8;
const int precision = 3;

void Test_sizeof();
void Test_subscript_ops();
void Test_comparison_ops();

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void TestMatrix()
{
    Test_sizeof();
    Test_subscript_ops();
    Test_comparison_ops();
}

void Test_sizeof()
{
    cout << "sizeof(3x3xfloat) = " << 3 * 3 * sizeof(float) << endl;
    cout << "sizeof(Matrix3f) = " << sizeof(Matrix3f) << endl;
    cout << endl;

    cout << "sizeof(3x3xdouble) = " << 3 * 3 * sizeof(double) << endl;
    cout << "sizeof(Matrix3d) = " << sizeof(Matrix3d) << endl;
    cout << endl;

    cout << "sizeof(4x4xdouble) = " << 4 * 4 * sizeof(double) << endl;
    cout << "sizeof(Matrix4d) = " << sizeof(Matrix4d) << endl;
    cout << endl;

    cout << "sizeof(6x6xdouble) = " << 6 * 6 * sizeof(double) << endl;
    cout << "sizeof(Matrix6d) = " << sizeof(Matrix6d) << endl;
    cout << endl;

    cout << "sizeof(3xfloat) = " << 3 * sizeof(float) << endl;
    cout << "sizeof(Vector3f) = " << sizeof(Vector3f) << endl;
    cout << endl;

    cout << "sizeof(3xdouble) = " << 3 * sizeof(double) << endl;
    cout << "sizeof(Vector3d) = " << sizeof(Vector3d) << endl;
    cout << endl;
}

void Test_subscript_ops()
{
    cout << setprecision(precision);

    open3d::Matrix3f m =
    {
         0.0f, 1.0f, 2.0f ,
         3.0f, 4.0f, 5.0f ,
         6.0f, 7.0f, 8.0f
    };

    cout << "[][] access for Matrix<float, 3, 3> type:" << endl;
    cout << setw(width) << m[0][0];
    cout << setw(width) << m[0][1];
    cout << setw(width) << m[0][2] << endl;
    cout << setw(width) << m[1][0];
    cout << setw(width) << m[1][1];
    cout << setw(width) << m[1][2] << endl;
    cout << setw(width) << m[2][0];
    cout << setw(width) << m[2][1];
    cout << setw(width) << m[2][2] << endl;
    cout << endl;

    open3d::Vector3f v = { 0.0f, 0.1f, 0.2f };

    cout << "[] access for Vector<float, 3> type:" << endl;
    cout << setw(width) << v.s[0];
    cout << setw(width) << v.s[1];
    cout << setw(width) << v.s[2] << endl;

    cout << setw(width) << v[0];
    cout << setw(width) << v[1];
    cout << setw(width) << v[2] << endl;
    cout << endl;

    open3d::Vector3f v3 = { 3.0f, 3.1f, 3.2f };

    cout << "[] access for Vector3<float> type:" << endl;
    cout << setw(width) << v3.s[0];
    cout << setw(width) << v3.s[1];
    cout << setw(width) << v3.s[2] << endl;

    cout << setw(width) << v3[0];
    cout << setw(width) << v3[1];
    cout << setw(width) << v3[2] << endl;
    cout << endl;
}

void Test_comparison_ops()
{
    open3d::Matrix3f m0 =
    {
         0.0f, 1.0f, 2.0f ,
         3.0f, 4.0f, 5.0f ,
         6.0f, 7.0f, 8.0f
    };

    open3d::Matrix3f m1 =
    {
         0.0f, 1.0f, 2.0f ,
         3.0f, 4.0f, 5.0f ,
         6.0f, 7.0f, 8.0f
    };

    cout << "m0 is" << ((m0 == m1) ? "" : " not") << " equal to m1." << endl;
    cout << endl;

    open3d::Vector3f v0 = { 0.0f, 0.1f, 0.2f };
    open3d::Vector3f v1 = { 0.0f, 0.1f, 0.2f };

    cout << "v0 is" << ((v0 == v1) ? "" : " not") << " equal to v1." << endl;
    cout << endl;
}
