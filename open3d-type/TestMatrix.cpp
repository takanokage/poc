
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

    open3d::Matrix<float, 3, 3>::Type m;

    open3d::Vector<float, 3> v = { 1.0f, 1.1f, 1.2f };

    open3d::Vector3<float> v3 = { 0.0f, 0.1f, 0.2f };

    cout << setw(width) << v3.s[0][0];
    cout << setw(width) << v3.s[1][0];
    cout << setw(width) << v3.s[2][0] << endl;
    cout << endl;
}
