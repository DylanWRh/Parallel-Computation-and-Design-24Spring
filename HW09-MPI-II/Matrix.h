#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <class T>
class Matrix {
public:
    int nrows = 0;
    int ncols = 0;

    T **d = nullptr;

    Matrix();
    Matrix(const int &nrows_, const int &ncols_, const bool flag_zero = true);
    ~Matrix();

    void set_zero();
    void set_zero(const int &nrows_, const int &ncols_);

    T get_max() const;
    T get_min() const;

    Matrix<T> operator+(const Matrix<T> &mat) const;
    Matrix<T> operator-(const Matrix<T> &mat) const;
    Matrix<T> operator*(const Matrix<T> &mat) const;

    template<class _T>friend std::ostream& operator<<(std::ostream& os, const Matrix<_T>& mat);
    template<class _T>friend std::istream& operator>>(std::istream& is, Matrix<_T>& mat);
};

#endif
