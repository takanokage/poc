
#include "Halide.h"

#include <cfloat>
#include <climits>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include "rand.h"

typedef float Point[3];

float distance(const Point& p0, const Point& p1);

int main(int argc, char **argv)
{
    size_t N = 10;
    float lo_bound = 0.0f;
    float hi_bound = 10.0f;

    int p = 2;
    int w = 5;
    cout << setprecision(p);
    cout << fixed;

    cout << "knn" << endl;
    cout << endl;

    vector<Point> points(N);
    for (size_t i = 0; i < points.size(); i++)
    {
        points[i][0] = RAND::value<float>(lo_bound, hi_bound);
        points[i][1] = RAND::value<float>(lo_bound, hi_bound);
        points[i][2] = RAND::value<float>(lo_bound, hi_bound);
    }

    cout << "define some points" << endl;
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << setw(w) << points[i][0];
        cout << setw(w) << points[i][1];
        cout << setw(w) << points[i][2];
        cout << endl;
    }
    cout << endl;

    vector<size_t> indices(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        float mind = FLT_MAX;
        for (size_t j = 0; j < points.size(); j++)
        {
            if (i == j) continue;

            float d = distance(points[i], points[j]);

            indices[i] = d < mind ? j : indices[i];
            mind = d < mind ? d : mind;
        }
    }

    cout << "results after knn:1" << endl;
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << setw(w) << i;
        cout << " : ";
        cout << setw(w) << indices[i];
        cout << endl;
    }
    cout << endl;

    return 0;
}

float distance(const Point& p0, const Point& p1)
{
    float d0 = p0[0] - p1[0];
    float d1 = p0[1] - p1[1];
    float d2 = p0[2] - p1[2];

    return sqrt(d0 * d0 + d1 * d1 + d2 * d2);
}
