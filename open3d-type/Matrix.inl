
// // ****************************************************************************
// // 2D tensor, row major
// // Matrix <typename T, uint ROWS, uint COLS>
// // ****************************************************************************

// template <typename T, uint ROWS, uint COLS>
// T *open3d::Matrix<T, ROWS, COLS>::Type::operator[](const uint &i) {
//     // catch error in debug mode
//     assert(0 <= i && i < 3);

//     return (T *)&s[i];
// }

// template <typename T, uint ROWS, uint COLS>
// const T *open3d::Matrix<T, ROWS, COLS>::Type::operator[](const uint &i) const {
//     // catch error in debug mode
//     assert(0 <= i && i < 3);

//     return (const T *const) & s[i];
// }

// template <typename T, uint ROWS, uint COLS>
// open3d::Matrix<T, ROWS, COLS>::Type::operator T *const() {
//     return reinterpret_cast<T *>(s);
// }

// template <typename T, uint ROWS, uint COLS>
// open3d::Matrix<T, ROWS, COLS>::Type::operator const T *const() {
//     return reinterpret_cast<const T *const>(s);
// }

// template <typename T, uint ROWS, uint COLS>
// bool open3d::Matrix<T, ROWS, COLS>::Type::operator==(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++)
//             if ((*this)[r][c] != m[r][c]) return false;

//     return true;
// }

// template <typename T, uint ROWS, uint COLS>
// bool open3d::Matrix<T, ROWS, COLS>::Type::operator!=(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     return !(*this == m);
// }

// template <typename T, uint ROWS, uint COLS>
// bool open3d::Matrix<T, ROWS, COLS>::Type::operator<=(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++)
//             if ((*this)[r][c] > m[r][c]) return false;

//     return true;
// }

// template <typename T, uint ROWS, uint COLS>
// bool open3d::Matrix<T, ROWS, COLS>::Type::operator>=(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     for (uint r = 0; r < ROWS; r++)
//         if ((*this)[r] < m[r]) return false;

//     return true;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
// open3d::Matrix<T, ROWS, COLS>::Type::operator+(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] + m[r][c];

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
// open3d::Matrix<T, ROWS, COLS>::Type::operator-(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] - m[r][c];

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator+=(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] += m[r][c];

//     return *this;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator-=(
//         const typename open3d::Matrix<T, ROWS, COLS>::Type &m) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] -= m[r][c];

//     return *this;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
// open3d::Matrix<T, ROWS, COLS>::Type::operator+(const T &t) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] + t;

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
// open3d::Matrix<T, ROWS, COLS>::Type::operator-(const T &t) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] - t;

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
//         open3d::Matrix<T, ROWS, COLS>::Type::operator*(const T &t) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] * t;

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type
// open3d::Matrix<T, ROWS, COLS>::Type::operator/(const T &t) const {
//     Matrix<T, ROWS, COLS>::Type output;
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) output[r][c] = (*this)[r][c] / t;

//     return output;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator+=(const T &t) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] += t;

//     return *this;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator-=(const T &t) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] -= t;

//     return *this;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator*=(const T &t) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] *= t;

//     return *this;
// }

// template <typename T, uint ROWS, uint COLS>
// typename open3d::Matrix<T, ROWS, COLS>::Type &
// open3d::Matrix<T, ROWS, COLS>::Type::operator/=(const T &t) {
//     for (uint r = 0; r < ROWS; r++)
//         for (uint c = 0; c < COLS; c++) (*this)[r][c] /= t;

//     return *this;
// }

// // ****************************************************************************
// // 1D tensor, row major
// // Matrix <typename T, 1, uint COLS>
// // ****************************************************************************

// template <typename T, uint COLS>
// T &open3d::Matrix<T, 1, COLS>::Type::operator[](const uint &i) {
//     // catch error in debug mode
//     assert(0 <= i && i < 3);

//     return s[i];
// }

// template <typename T, uint COLS>
// const T &open3d::Matrix<T, 1, COLS>::Type::operator[](const uint &i) const {
//     // catch error in debug mode
//     assert(0 <= i && i < 3);

//     return s[i];
// }

// template <typename T, uint COLS>
// open3d::Matrix<T, 1, COLS>::Type::operator T *const() {
//     return reinterpret_cast<T *>(s);
// }

// template <typename T, uint COLS>
// open3d::Matrix<T, 1, COLS>::Type::operator const T *const() {
//     return reinterpret_cast<const T *const>(s);
// }

// template <typename T, uint COLS>
// bool open3d::Matrix<T, 1, COLS>::Type::operator==(
//         const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     for (uint c = 0; c < COLS; c++)
//         if ((*this)[c] != v[c]) return false;

//     return true;
// }

// template <typename T, uint COLS>
// bool open3d::Matrix<T, 1, COLS>::Type::operator!=(
//         const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     return !(*this == v);
// }

// template <typename T, uint COLS>
// bool open3d::Matrix<T, 1, COLS>::Type::operator<=(
//         const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     for (uint c = 0; c < COLS; c++)
//         if ((*this)[c] > v[c]) return false;

//     return true;
// }

// template <typename T, uint COLS>
// bool open3d::Matrix<T, 1, COLS>::Type::operator>=(
//         const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     for (uint c = 0; c < COLS; c++)
//         if ((*this)[c] < v[c]) return false;

//     return true;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator+(const typename open3d::Matrix<T, 1, COLS>::Type &v) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] + v[c];

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator-(const typename open3d::Matrix<T, 1, COLS>::Type &v) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] - v[c];

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator+=(const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] += v[c];

//     return *this;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator-=(const typename open3d::Matrix<T, 1, COLS>::Type &v) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] -= v[c];

//     return *this;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator+(const T &t) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] + t;

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator-(const T &t) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] - t;

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator*(const T &t) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] * t;

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type open3d::Matrix<T, 1, COLS>::Type::
// operator/(const T &t) const {
//     Matrix<T, 1, COLS>::Type output;
//     for (uint c = 0; c < COLS; c++) output[c] = (*this)[c] / t;

//     return output;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator+=(const T &t) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] += t;

//     return *this;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator-=(const T &t) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] -= t;

//     return *this;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator*=(const T &t) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] *= t;

//     return *this;
// }

// template <typename T, uint COLS>
// typename open3d::Matrix<T, 1, COLS>::Type &open3d::Matrix<T, 1, COLS>::Type::
// operator/=(const T &t) {
//     for (uint c = 0; c < COLS; c++) (*this)[c] /= t;

//     return *this;
// }
