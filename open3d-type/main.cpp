#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "types.h"
using namespace open3d;
using namespace open3d::DIM;

#include "performance.h"

int main(int argc, char **argv)
{
    open3d::Vector3f v;

    cout << "open3d::Vector3f v" << endl;
    cout << "is POD? " << (is_pod<open3d::Vector3f>() ? "true" : "false") << endl;
    cout << endl;

    cout << "indexing using subscript operator" << endl;
    v[X] = 1.0;
    v[Y] = 1.1;
    v[Z] = 1.2;

    // this line will fail in Debug mode due to assert in subscript operator
    // it will run fine in Release mode, it just won't do anything
    v[W] = 1.3;

    cout << v << endl;
    cout << endl;

    printf("%4.1f\n", v[0]);
    printf("%4.1f\n", v[1]);
    printf("%4.1f\n", v[2]);
    cout << endl;

    cout << "indexing using x, y, z named members" << endl;
    v.x = 2.0;
    v.y = 2.1;
    v.z = 2.2;

    cout << v << endl;
    cout << endl;

    cout << "indexing using r, g, b named members" << endl;
    cout << v << endl;
    cout << endl;

    cout << "alignment" << endl;
    cout << "sizeof(3xfloat):    " << 3 * sizeof(float) << endl;
    cout << "type alignment:     " << sizeof(open3d::Vector3f) << endl;
    cout << "variable alignment: " << sizeof(v) << endl;
    cout << endl;

    cout << "initalization using initializer list" << endl;
    open3d::Vector3f v2 = { 3.0f, 3.1f, 3.2f };

    cout << v2 << endl;
    cout << endl;

    cout << "cast to a float*" << endl;
    open3d::Vector3f v3 = { 5.0f, 5.1f, 5.2f };
    float* vfloat = (float*)v3;

    vfloat[0] = 6.0f;
    vfloat[1] = 6.1f;
    vfloat[2] = 6.2f;

    cout << v3 << endl;
    cout << endl;

    cout << v3 << endl;
    cout << endl;

    cout << "const operator[] test" << endl;
    const open3d::Vector3f v8 = { 8.0f, 8.1f, 8.2f };

    cout << v8 << endl;
    cout << endl;

    int loops = (int)1e7;
    srand(0);
    float b[3] = { -0.1f, -0.2f, -0.3f };
    for (int i = 0; i < loops; i++)
        b[i % 3] = b[rand() % 3];
    cout << "measure performance of float[3] using " << loops << " loops" << endl;
    Performance::Start();
    for (int i = 0; i < loops; i++)
        b[i % 3] = b[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << b << endl;
    cout << endl;

    srand(0);
    cout << "measure performance of custom[] using " << loops << " loops" << endl;
    v = { 5.0f, 5.1f, 5.2f };
    Performance::Start();
    for (int i = 0; i < loops; i++)
        v[i % 3] = v[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << v << endl;
    cout << endl;

    srand(0);
    cout << "measure performance of (float*)[] using " << loops << " loops" << endl;
    v = { 6.0f, 6.1f, 6.2f };
    float* const a = (float* const)v;
    // for (int i = 0; i < loops; i++)
    //     a[i % 3] = a[rand() % 3];
    Performance::Start();
    for (int i = 0; i < loops; i++)
        ((float*)a)[i % 3] = ((float*)a)[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << a << endl;
    cout << endl;

    cout << "const operator== test" << endl;
    const open3d::Vector3f v9  = { 9.0f, 9.1f, 9.2f };
    const open3d::Vector3f v10 = { 9.0f, 9.1f, 9.2f };
    cout << "v9 is " << ((v9 == v10) ? "" : "not") << " equal to v10." << endl;

    cout << v8 << endl;
    cout << endl;

    cout << "sort test" << endl;
    vector<open3d::Vector3f> points(10);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 3; j++)
            points[i][j] = (float)rand() / RAND_MAX;

    cout << "original data:" << endl;
    for (int i = 0; i < 10; i++)
        cout << points[i] << endl;
    cout << endl;

    cout << "sort ascending on X:" << endl;
    sort(points.begin(), points.end(), open3d::Vector3f::LEX);
    for (int i = 0; i < 10; i++)
        cout << points[i] << endl;
    cout << endl;

    cout << "sort ascending on Y:" << endl;
    sort(points.begin(), points.end(), open3d::Vector3f::LEY);
    for (int i = 0; i < 10; i++)
        cout << points[i] << endl;
    cout << endl;

    cout << "sort ascending on Z:" << endl;
    sort(points.begin(), points.end(), open3d::Vector3f::LEZ);
    for (int i = 0; i < 10; i++)
        cout << points[i] << endl;
    cout << endl;

    cout << "test operators:" << endl;
    open3d::Vector3f va = { 2.3f, 2.4f, 2.5f };
    open3d::Vector3f vb = { 3.2f, 4.2f, 5.2f };
    open3d::Vector3f vc = va + vb;
    cout << va << " + " << endl;
    cout << vb << " = " << endl;
    cout << vc << endl;
    cout << endl;

    open3d::Vector3f vd = va - vb;
    cout << va << " - " << endl;
    cout << vb << " = " << endl;
    cout << vd << endl;
    cout << endl;

    cout.unsetf(ios::fixed);

    float value = 3.5;
    open3d::Vector3f ve = va * value;
    cout << va << " * ";
    cout << value << " = " << endl;
    cout << ve << endl;
    cout << endl;

    open3d::Vector3f vf = va / value;
    cout << va << " / ";
    cout << value << " = " << endl;
    cout << vf << endl;
    cout << endl;

    open3d::Vector3f vg = va; vg += vb;
    cout << vg << " += " << endl;
    cout << vb << endl;
    cout << vg << endl;
    cout << endl;

    open3d::Vector3f vh = va; vh -= vb;
    cout << vh << " -= " << endl;
    cout << vb << endl;
    cout << vh << endl;
    cout << endl;

    return 0;
}
