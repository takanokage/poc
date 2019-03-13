
#include <cassert>
#include <climits>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define WIDTH 10

void basicTest();
int solution(vector<int> &a, vector<int> &b);
void display(vector<int> &a, vector<int> &b);
void stressTest(const int &size, const int& nrLoops = 1);

int main(int argc, char **argv) {
    // basicTest();

    int size = 10000;
    stressTest(size, 10);

    return 0;
}

void stressTest(const int &size, const int& nrLoops) {
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

    for (int l = 0; l < nrLoops; l++)
        pairs = solution(a, b);

    cout << "pairs: " << pairs << endl;
    cout << endl;
}

void basicTest() {
    cout << "Basic Test" << endl;
    cout << endl;

    vector<int> a = {0, 1, 2, 2, 3, 5};
    vector<int> b = {500000, 500000, 0, 0, 0, 20000};

    display(a, b);

    int pairs = solution(a, b);
    cout << "pairs: " << pairs << endl;
    cout << endl;
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

void display(vector<int> &a, vector<int> &b) {
    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << p;
    cout << endl;

    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << a[p];
    cout << endl;

    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << b[p];
    cout << endl;
}
