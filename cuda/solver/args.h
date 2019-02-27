
#ifndef ARGS_H
#define ARGS_H

#include <cstring>

namespace Args
{
    // Pointer to:
    //   int   __cdecl atoi(_In_z_ const char *_Str)
    //   long  __cdecl atol(_In_z_ const char *_Str)
    // double  __cdecl atof(_In_z_ const char *_Str)
    template<class T> struct Converter
    {
        typedef T(*Type)(const char* in);
    };

    // Command line arguments.
    typedef struct _Type
    {
        // single precision
        bool sp;

        // double precision
        bool dp;

        // size of matrix A
        int size;

        // device id
        int devID;
    } Type;

    // Convert a std::string to a value (no blank spaces allowed).
    // The 'converter' must be one of:
    // - atoi for int.
    // - atol for long.
    // - atof for double.
    template<class T>
    bool GetValue
        (
        const char* const arg,
        const char* const argv[],
        int& i,
        typename Converter<T>::Type converter,
        T& value
        )
    {
        if (strcmp(argv[i], arg) != 0)
            return false;

        i++;

        value = converter(argv[i]);

        return true;
    }

    // Change a flag.
    bool ChangeFlag(
        const char* const arg,
        const char* const argv[],
        int& i,
        bool& flag);

    // Interpret command line arguments.
    Type Interpret(int argc, char* argv[]);

    // display help.
    void Help();
}

#endif