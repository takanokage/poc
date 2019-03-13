
#include <climits>

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int solution(vector<int> &A);

int main(int argc, char **argv) {
    vector<int> a = {2, -4, 6, -3, 9};

    for (int p = 0; p < a.size(); p++) cout << setw(4) << p;
    cout << endl;

    for (int p = 0; p < a.size(); p++) cout << setw(4) << a[p];
    cout << endl;

    int minSum = solution(a);
    cout << "min sum: " << minSum << endl;

    return 0;
}

// slice
int solution(vector<int> &a) {
    int minSum = INT_MAX;

    for (int p = 0; p < a.size(); p++) {
        for (int q = p + 1; q < a.size(); q++) {
            int sum = 0;
            for (int i = p; i < q; i++) sum += a[i];

            sum = abs(sum);

            if (sum < minSum) minSum = sum;
        }
    }

    return minSum;
}
