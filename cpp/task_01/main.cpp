
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int solution(vector<int> &A);

int main(int argc, char **argv) {
    vector<int> a = {0, 1, 3, -2, 0, 1, 0, -3, 2, 3};

    for (int i = 0; i < a.size(); i++) cout << setw(4) << i;
    cout << endl;

    for (int i = 0; i < a.size(); i++) cout << setw(4) << a[i];
    cout << endl;

    int maxPit = solution(a);
    cout << "max pit: " << maxPit << endl;

    return 0;
}

// pit
int solution(vector<int> &a) {
    int maxPit = 0;

    uint pitStart = 0;
    uint pitEnd = 0;

    for (size_t i = 1; i < a.size() - 1; i++) {
        // search left
        int right = a[i];
        for (int l = i - 1; 0 <= l; l--) {
            if (a[l] < right) break;

            pitStart = l;
            right = a[l];
        }

        // search right
        int left = a[i];
        for (size_t r = i + 1; r < a.size(); r++) {
            if (left > a[r]) break;

            pitEnd = r;
            left = a[r];
        }

        int pit = min(a[pitEnd] - a[i], a[pitStart] - a[i]);

        if (maxPit < pit) maxPit = pit;
    }

    return maxPit;
}
