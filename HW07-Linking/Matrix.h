#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
public:
    int nrows = 0;
    int ncols = 0;

    double **d = nullptr;

    Matrix();
    Matrix(const int &nrows_, const int &ncols_, const bool flag_zero = true);
    ~Matrix();

    void set_zero();
    void set_zero(const int &nrows_, const int &ncols_);

    double get_max() const;
    double get_min() const;

    Matrix operator+(const Matrix &mat) const;
    Matrix operator-(const Matrix &mat) const;
    Matrix operator*(const Matrix &mat) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
    friend std::istream& operator>>(std::istream& is, Matrix& mat);
};

// Calculate matrix multiplication of matA and matB and write result to a new Matrix
Matrix call_dgemm(const Matrix &matA, const Matrix &matB);

#endif
