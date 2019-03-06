
#include "Matrix.h"
using namespace open3d;

#include "types.h"
using namespace open3d::DIM;

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "performance.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void TestMatrix()
{
    int width = 8;
    int precision = 3;
    cout << setprecision(precision);

    open3d::Matrix<float, 3, 3>::Type m =
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

    open3d::Vector<float, 3> v = { 0.0f, 0.1f, 0.2f };

    cout << "[] access for Vector<float, 3> type:" << endl;
    cout << setw(width) << v.s[0];
    cout << setw(width) << v.s[1];
    cout << setw(width) << v.s[2] << endl;

    cout << setw(width) << v[0];
    cout << setw(width) << v[1];
    cout << setw(width) << v[2] << endl;
    cout << endl;

    open3d::Vector3<float> v3 = { 3.0f, 3.1f, 3.2f };

    cout << "[] access for Vector3<float> type:" << endl;
    cout << setw(width) << v3.s[0];
    cout << setw(width) << v3.s[1];
    cout << setw(width) << v3.s[2] << endl;

    cout << setw(width) << v3[0];
    cout << setw(width) << v3[1];
    cout << setw(width) << v3[2] << endl;
    cout << endl;
}
