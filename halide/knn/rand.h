#ifndef RAND_H
#define RAND_H

namespace RAND
{
    // Get a random value in the specified range.
    template<class T>
    T value(const T& vmin, const T& vmax)
    {
        return vmin + (T)std::rand() * (vmax - vmin) / RAND_MAX;
    }

    // Get a random value in the (0,1) range.
    template<class T>
    T value()
    {
        return (T)std::rand() / RAND_MAX;
    }

    // Initialize an array with random values in the specified range.
    template<class T>
    void array(const T& vmin, const T& vmax, T *const v, const size_t& vsize)
    {
        T factor = (T)(vmax - vmin) / RAND_MAX;

        for (size_t i = 0; i < vsize; i++)
            v[i] = vmin + (T)std::rand() * factor;
    }

    // Initialize an array with random values in the (0,1) range.
    template<class T>
    void array(T *const v, const size_t& vsize)
    {
        T factor = (T)1 / RAND_MAX;

        for (size_t i = 0; i < vsize; i++)
            v[i] = (T)std::rand() * factor;
    }
}

#endif
