
#include <climits>

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int solution(vector<int> &a, vector<int> &b);

#define WIDTH 10

int main(int argc, char **argv) {
    vector<int> a = {0, 1, 2, 2, 3, 5};
    vector<int> b = {500000, 500000, 0, 0, 0, 20000};

    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << p;
    cout << endl;

    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << a[p];
    cout << endl;

    for (int p = 0; p < a.size(); p++) cout << setw(WIDTH) << b[p];
    cout << endl;

    int pairs = solution(a, b);
    cout << "pairs: " << pairs << endl;

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
