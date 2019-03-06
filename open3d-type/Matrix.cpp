
#include <cassert>
#include <cmath>

#include "Matrix.h"

#include <iomanip>
using namespace std;

// ----------------------------------------------------------------------------
// subscript operator: readwrite
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
T& open3d::Matrix<T, R, C>::Type::operator [](const uint& i)
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((T*)this)[i];
}

// ----------------------------------------------------------------------------
// subscript operator: readonly
// ----------------------------------------------------------------------------
template<typename T, uint R, uint C>
const T& open3d::Matrix<T, R, C>::Type::operator [](const uint& i) const
{
    // catch error in debug mode
    assert(0 <= i && i < 3);

    return ((const T* const)this)[i];
}

// Template instantiations:
template class open3d::Matrix<float, 3, 1>;
