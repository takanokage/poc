
#include "args.h"

#include <cstdlib>

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Interpret command line arguments.
// ----------------------------------------------------------------------------
Args::Type Args::Interpret(int argc, char* argv[])
{
    Type args = { false, false, 1024, 0 };

    for (int i = 0; i < argc; i++)
    {
        if (strcmp("-h", argv[i]) == 0)
        {
            Help();
            break;
        }

        if (argc == 1)
        {
            Help();
            break;
        }

        if (ChangeFlag("-sp", argv, i, args.sp))
            continue;

        if (ChangeFlag("-dp", argv, i, args.dp))
            continue;

        if (GetValue("-n", argv, i, atoi, args.size))
            continue;

        if (GetValue("-d", argv, i, atoi, args.devID))
            continue;
    }

    return args;
}

// ----------------------------------------------------------------------------
// Change a flag.
// ----------------------------------------------------------------------------
bool Args::ChangeFlag(
    const char* const arg,
    const char* const argv[],
    int& i,
    bool& flag)
{
    if (strcmp(argv[i], arg) != 0)
        return false;

    flag = !flag;

    return true;
}

// ----------------------------------------------------------------------------
// Display help.
// ----------------------------------------------------------------------------
void Args::Help()
{
    cout << "Solve a randomly initialized dense A*x=b equation." << endl;
    cout << "   arguments:" << endl;
    cout << "       -sp:      single precision" << endl;
    cout << "       -dp:      double precision" << endl;
    cout << "       -n SIZE:  size of matrix A (default 1024)" << endl;
    cout << "       -d index: device id (default 0)" << endl;
    cout << endl;
    cout << "   Notes:" << endl;
    cout << "       - the precision argument is mandatory." << endl;
    cout << "       - specifying both '-sp' and '-dp' will perform the test in both precisions." << endl;
    cout << endl;
}