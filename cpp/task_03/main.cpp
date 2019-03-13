
#include <cassert>
#include <climits>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#include <chrono>
using namespace chrono;
using hiResClock = std::chrono::high_resolution_clock;

#define WIDTH 15

int solution(vector<int> &a, vector<int> &b);
void BasicTest();
void StressTest(const int &size, const int &nrLoops = 1);
void Display(vector<int> &a, vector<int> &b);
double Duration(const hiResClock::time_point &start,
                const hiResClock::time_point &stop);

int main(int argc, char **argv) {
    // BasicTest();

    int size = atoi(argv[1]);
    int nrLoops = atoi(argv[2]);
    StressTest(size, nrLoops);

    return 0;
}

// pairs
int solution(vector<int> &a, vector<int> &b) {
    int pairs = 0;

    for (size_t p = 0; p < a.size() - 1; p++) {
        float P = a[p] + b[p] / 1e6f;

        for (size_t q = p + 1; q < a.size(); q++) {
            float Q = a[q] + b[q] / 1e6f;

            float mul = P * Q;
            float sum = P + Q;

            if (mul >= sum) pairs++;
        }
    }

    return min(pairs, (int)1e9);
}

// perform a test on randomly initialized a and b vectors
// measure the average execution time over a number of loops
void StressTest(const int &size, const int &nrLoops) {
    cout << "Stress Test" << endl;
    cout << endl;

    assert(size <= (int)1e5);

    vector<int> a(size);
    vector<int> b(size);

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        a[i] = (int)(1e3f * rand() / RAND_MAX);
        b[i] = (int)((1e6f - 1) * rand() / RAND_MAX);
    }

    int pairs = 0;

    hiResClock::time_point start = hiResClock::now();
    for (int l = 0; l < nrLoops; l++) pairs = solution(a, b);
    hiResClock::time_point stop = hiResClock::now();

    double exeTime = Duration(start, stop) / nrLoops;

    cout << setw(WIDTH) << "N: " << size << endl;
    cout << setw(WIDTH) << "nr. loops: " << nrLoops << endl;
    cout << setw(WIDTH) << "pairs: " << pairs << endl;
    cout << setw(WIDTH) << "duration: " << exeTime << "ms" << endl;
    cout << endl;
}

// perform a basic test.
// a and b vectors are predefined
// the correct answer is known.
void BasicTest() {
    cout << "Basic Test" << endl;
    cout << endl;

    vector<int> a = {0, 1, 2, 2, 3, 5};
    vector<int> b = {500000, 500000, 0, 0, 0, 20000};

    Display(a, b);

    int pairs = solution(a, b);
    cout << "pairs: " << pairs << endl;
    cout << endl;
}

// display both vectors for debugging purposes.
void Display(vector<int> &a, vector<int> &b) {
    for (size_t p = 0; p < a.size(); p++) cout << setw(WIDTH) << p;
    cout << endl;

    for (size_t p = 0; p < a.size(); p++) cout << setw(WIDTH) << a[p];
    cout << endl;

    for (size_t p = 0; p < a.size(); p++) cout << setw(WIDTH) << b[p];
    cout << endl;
}

// calculate the time, in ms, between two events.
double Duration(const hiResClock::time_point &start,
                const hiResClock::time_point &stop) {
    double us = duration_cast<microseconds>(stop - start).count();
    double ms = us / 1000.0;

    return ms;
}
