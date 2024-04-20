#include "Matrix.h"
#include <limits>
#include <cassert>
#include <sstream>
#include <stdexcept>

template <class T>
Matrix<T>::Matrix() {}

template <class T>
Matrix<T>::Matrix(const int &nrows_, const int &ncols_, const bool flag_zero) : nrows(nrows_), ncols(ncols_) {
    d = new T*[nrows];
    d[0] = new T[nrows * ncols]; // Contiguous block
    for (int i = 0; i < nrows; ++i) {
        d[i] = d[0] + i * ncols;
    }
    if (flag_zero) {
        set_zero();
    }
}

template <class T>
Matrix<T>::~Matrix() {
    // delete[] d[0];
    // delete[] d;
}

template <class T>
void Matrix<T>::set_zero() {
    // Timer::tick("Matrix", "set_zero()");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] = 0.0;
        }
    }
    // Timer::tick("Matrix", "set_zero()");
}

template<class T>
void Matrix<T>::set_zero(const int &nrows_, const int &ncols_) {
    // Timer::tick("Matrix", "set_zero(const int &, const int &)");
    if (d) {
        for (int i = 0; i < nrows; ++i) {
            delete[] d[i];
        }
        delete[] d;
    }
    nrows = nrows_;
    ncols = ncols_;
    d = new T*[nrows];
    for (int i = 0; i < nrows; ++i) {
        d[i] = new T[ncols];
    }
    set_zero();
    // Timer::tick("Matrix", "set_zero(const int &, const int &)");
}

template <class T>
T Matrix<T>::get_max() const {
    T max_val = std::numeric_limits<T>::lowest();
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            if (d[i][j] > max_val) {
                max_val = d[i][j];
            }
        }
    }
    return max_val;
}

template <class T>
T Matrix<T>::get_min() const {
    T min_val = std::numeric_limits<T>::max();
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            if (d[i][j] < min_val) {
                min_val = d[i][j];
            }
        }
    }
    return min_val;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat) const {
    if (nrows != mat.nrows || ncols != mat.ncols) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    Matrix result(nrows, ncols, false);

    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            result.d[i][j] = d[i][j] + mat.d[i][j];
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mat) const {
    if (nrows != mat.nrows || ncols != mat.ncols) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    Matrix result(nrows, ncols, false);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            result.d[i][j] = d[i][j] - mat.d[i][j];
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mat) const {
    assert (ncols == mat.nrows);

    // std::ostringstream oss;
    // oss << "MatMul, (" << nrows << "," << ncols << ") *";
    // oss << " (" << mat.nrows << "," << mat.ncols << ")";
    // Timer::tick("Matrix", oss.str());
    
    Matrix result(nrows, mat.ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < mat.ncols; ++j) {
            int sum = 0;
            for (int k = 0; k < ncols; ++k) {
                sum += d[i][k] * mat.d[k][j];
            }
            result.d[i][j] = sum;
        }
    }

    // Timer::tick("Matrix", oss.str());
    return result;
}

template <class _T>
std::ostream& operator<<(std::ostream& os, const Matrix<_T>& matrix) {
    for (int i = 0; i < matrix.nrows; ++i) {
        for (int j = 0; j < matrix.ncols; ++j) {
            os << matrix.d[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

template <class _T>
std::istream& operator>>(std::istream& is, Matrix<_T>& matrix) {
    for (int i = 0; i < matrix.nrows; ++i) {
        for (int j = 0; j < matrix.ncols; ++j) {
            is >> matrix.d[i][j];
        }
    }
    return is;
}
