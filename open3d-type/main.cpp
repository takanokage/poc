#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "types.h"

#include "performance.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

int main(int argc, char **argv)
{
    int width = 4;
    int precision = 1;

    cout << setprecision(precision);
    cout << fixed;

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

    cout << setw(width) << v[0];
    cout << setw(width) << v[1];
    cout << setw(width) << v[2];
    cout << setw(width) << v[3] << endl;
    cout << endl;

    printf("%4.1f\n", v[0]);
    printf("%4.1f\n", v[1]);
    printf("%4.1f\n", v[2]);
    printf("%4.1f\n", v[3]);
    cout << endl;

    cout << "indexing using x, y, z named members" << endl;
    v.x = 2.0;
    v.y = 2.1;
    v.z = 2.2;

    cout << setw(width) << v.x;
    cout << setw(width) << v.y;
    cout << setw(width) << v.z << endl;
    cout << endl;

    cout << "indexing using r, g, b named members" << endl;
    cout << setw(width) << v.r;
    cout << setw(width) << v.g;
    cout << setw(width) << v.b << endl;
    cout << endl;

    cout << "alignment" << endl;
    cout << "size:               " << 3 * sizeof(float) << endl;
    cout << "type alignment:     " << sizeof(open3d::Vector3f) << endl;
    cout << "variable alignment: " << sizeof(v) << endl;
    cout << endl;

    cout << "initalization using initializer list" << endl;
    open3d::Vector3f v2 = { 3.0f, 3.1f, 3.2f };

    cout << setw(width) << v2[0];
    cout << setw(width) << v2[1];
    cout << setw(width) << v2[2] << endl;
    cout << endl;

    cout << "cast to a float*" << endl;
    open3d::Vector3f v3 = { 5.0f, 5.1f, 5.2f };
    float* vf = v3;

    cout << setw(width) << vf[0];
    cout << setw(width) << vf[1];
    cout << setw(width) << vf[2];
    cout << setw(width) << vf[3] << endl;
    cout << endl;

    vf[0] = 6.0f;
    vf[1] = 6.1f;
    vf[2] = 6.2f;
    vf[3] = 6.3f;

    cout << setw(width) << vf[0];
    cout << setw(width) << vf[1];
    cout << setw(width) << vf[2];
    cout << setw(width) << vf[3] << endl;
    cout << endl;

    cout << setw(width) << v3[0];
    cout << setw(width) << v3[1];
    cout << setw(width) << v3[2];
    cout << setw(width) << v3[3] << endl;
    cout << endl;

    cout << "const operator[] test" << endl;
    const open3d::Vector3f v8 = { 8.0f, 8.1f, 8.2f };

    cout << setw(width) << v8[0];
    cout << setw(width) << v8[1];
    cout << setw(width) << v8[2];
    cout << setw(width) << v8[3];
    cout << setw(width) << v8[4] << endl;
    cout << endl;

    int loops = (int)1e7;
    cout << "measure performance of custom[] using " << loops << " loops" << endl;
    Performance::Start();
    for (int i = 0; i < loops; i++)
        v[i % 3] = v[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << setw(width) << v[0];
    cout << setw(width) << v[1];
    cout << setw(width) << v[2] << endl;
    cout << endl;

    cout << "measure performance of s[] using " << loops << " loops" << endl;
    Performance::Start();
    for (int i = 0; i < loops; i++)
        v.s[i % 3] = v.s[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << setw(width) << v.s[0];
    cout << setw(width) << v.s[1];
    cout << setw(width) << v.s[2] << endl;
    cout << endl;

    cout << "measure performance of (float*)[] using " << loops << " loops" << endl;
    float* const a = v;
    Performance::Start();
    for (int i = 0; i < loops; i++)
        a[i % 3] = a[rand() % 3];
    Performance::Stop();
    cout << "execution time: " << Performance::Duration() << " ms" << endl;
    cout << setw(width) << a[0];
    cout << setw(width) << a[1];
    cout << setw(width) << a[2] << endl;
    cout << endl;

    return 0;
}
