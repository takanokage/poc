
#include <cassert>
#include <cstdlib>
#include <ctime>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned int uint;

void TestGenerateGapSpecs(const int& nrTests = 10);
void TestGenerate(const uint& minSize, const uint& maxSize, const int& nrTests = 10);
void TestBits(const int& nrTests = 10);

void generateGapSpecs(const uint& minSize,
                    const uint& maxSize,
                    uint& size,
                    uint& gapStart,
                    uint& gapEnd);
int generate(const uint& size);
int generate(const uint& size, const uint& gapStart, const uint& gapEnd);
vector<uint> getBits(const int& n);
int getInt(const vector<uint>& bits);
string getString(const vector<uint>& bits);
int solution(int N);

int main(int argc, char** argv) {
    int nrTests = 10;

    TestGenerateGapSpecs(1000);
    // TestGenerate(7, 18);

    return 0;
}

// validate methods: generateGapSpecs
void TestGenerateGapSpecs(const int& nrTests) {
    cout << setw(10) << "size";
    cout << setw(10) << "gapStart";
    cout << setw(10) << "gapEnd";
    cout << endl;

    srand(time(NULL));
    for (int t = 0; t < nrTests; t++) {
        int minSize = 7;
        int maxSize = 32;
        uint size = 0;
        uint gapStart = 0;
        uint gapEnd = 0;

        generateGapSpecs(minSize, maxSize, size, gapStart, gapEnd);

        cout << setw(10) << size;
        cout << setw(10) << gapStart;
        cout << setw(10) << gapEnd;
        cout << endl;

        assert(gapStart <= gapEnd);
        assert(gapEnd <= size);
        assert(size <= 32);
    }
}

// validate methods: generate
void TestGenerate(const uint& minSize, const uint& maxSize, const int& nrTests) {
    srand(time(NULL));
    for (int t = 0; t < nrTests; t++) {
        uint size = 0;
        uint gapStart = 0;
        uint gapEnd = 0;

        generateGapSpecs(minSize, maxSize, size, gapStart, gapEnd);

        cout << setw(10) << size;
        cout << setw(10) << gapStart;
        cout << setw(10) << gapEnd;

        int in = generate(size, gapStart, gapEnd);

        vector<uint> bits = getBits(in);

        int out = getInt(bits);

        cout << setw(15) << in;
        cout << setw(40) << getString(bits);
        cout << setw(15) << out;
        cout << setw(10) << ((in == out) ? "PASSED" : "FAILED");
        cout << endl;
    }
}

// validate methods: getBits, getInt and getString
void TestBits(const int& nrTests) {
    srand(time(NULL));
    for (int t = 0; t < nrTests; t++) {
        int in = rand();
        vector<uint> bits = getBits(in);
        int out = getInt(bits);

        // convert bits to string
        stringstream binary;
        for (size_t i = 0; i < bits.size(); i++) binary << bits[i];

        cout << setw(15) << in;
        cout << setw(40) << getString(bits);
        cout << setw(15) << out;
        cout << setw(10) << ((in == out) ? "PASSED" : "FAILED");
        cout << endl;
    }
}

// generate binary gap specs
void generateGapSpecs(const uint& minSize,
                      const uint& maxSize,
                      uint& size,
                      uint& gapStart,
                      uint& gapEnd) {
    assert(2 < minSize);
    assert(minSize < maxSize);

    size = minSize + (uint)((maxSize - minSize) * (rand() / (float)RAND_MAX));
    gapStart = rand() % minSize;
    gapEnd = gapStart + (uint)((size - gapStart) * (rand() / (float)RAND_MAX));
}

// simply generate a random sequence of bits
int generate(const uint& size) {
    int output = 0;
    for (int i = 0; i < size; i++) {
        int bit = rand() % 2;
        cout << bit;

        output <<= 1;
        output += bit;
    }
    cout << endl;
    cout << output << endl;
    cout << endl;

    return output;
}

// generate a random sequence of bits with a gap within the specified boundary.
int generate(const uint& size, const uint& gapStart, const uint& gapEnd) {
    assert(gapStart <= gapEnd);
    assert(gapEnd <= size);
    assert(size <= 32);

    int output = 0;

    // random bits
    for (int i = 0; i < gapStart - 1; i++) {
        int bit = rand() % 2;

        output <<= 1;
        output += bit;
    }

    // start the gap
    output <<= 1;
    output += 1;

    // fill the gap
    for (int i = gapStart; i < gapEnd - 1; i++) {
        output <<= 1;
        output += 0;
    }

    // end the gap
    if (gapStart < gapEnd)
    {
        output <<= 1;
        output += 1;
    }

    // other random bits
    for (int i = gapEnd; i < size; i++) {
        int bit = rand() % 2;

        output <<= 1;
        output += bit;
    }

    return output;
}

// convert integer to a sequence of bits
vector<uint> getBits(const int& n) {
    vector<uint> bits(0);

    int failSafe = 64;

    int crtN = n;
    while (0 != crtN) {
        uint bit = abs(crtN % 2);
        bits.insert(bits.begin(), bit);
        crtN >>= 1;
    }

    return bits;
}

// convert a sequence of bits to an integer
int getInt(const vector<uint>& bits) {
    int output = 0;

    for (size_t i = 0; i < bits.size(); i++) {
        output <<= 1;
        output += bits[i];
    }

    return output;
}

// convert a sequence of bits to a string
string getString(const vector<uint>& bits) {
    stringstream binary;
    for (size_t i = 0; i < bits.size(); i++) binary << bits[i];

    return binary.str();
}

// parse an array of bits and return the size of the longest gap.
int solution(int N) { return 0; }