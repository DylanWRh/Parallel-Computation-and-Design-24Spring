#include "Matrix.h"
#include <cblas.h>
#include <lapacke.h>
#include <limits>
#include <cassert>
#include <sstream>
#include <stdexcept>

Matrix::Matrix() {}
Matrix::Matrix(const int &nrows_, const int &ncols_, const bool flag_zero) : nrows(nrows_), ncols(ncols_) {
    d = new double*[nrows];
    d[0] = new double[nrows * ncols]; // Contiguous block
    for (int i = 0; i < nrows; ++i) {
        d[i] = d[0] + i * ncols;
    }
    if (flag_zero) {
        set_zero();
    }
}

Matrix::~Matrix() {
    // delete[] d[0];
    // delete[] d;
}

void Matrix::set_zero() {
    // Timer::tick("Matrix", "set_zero()");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] = 0.0;
        }
    }
    // Timer::tick("Matrix", "set_zero()");
}

void Matrix::set_zero(const int &nrows_, const int &ncols_) {
    // Timer::tick("Matrix", "set_zero(const int &, const int &)");
    if (d) {
        for (int i = 0; i < nrows; ++i) {
            delete[] d[i];
        }
        delete[] d;
    }
    nrows = nrows_;
    ncols = ncols_;
    d = new double*[nrows];
    for (int i = 0; i < nrows; ++i) {
        d[i] = new double[ncols];
    }
    set_zero();
    // Timer::tick("Matrix", "set_zero(const int &, const int &)");
}

double Matrix::get_max() const {
    double max_val = std::numeric_limits<double>::lowest();
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            if (d[i][j] > max_val) {
                max_val = d[i][j];
            }
        }
    }
    return max_val;
}

double Matrix::get_min() const {
    double min_val = std::numeric_limits<double>::max();
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            if (d[i][j] < min_val) {
                min_val = d[i][j];
            }
        }
    }
    return min_val;
}

Matrix Matrix::operator+(const Matrix &mat) const {
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

Matrix Matrix::operator-(const Matrix &mat) const {
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

Matrix Matrix::operator*(const Matrix &mat) const {
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

void Matrix::read_symm(std::istream& is) {
    assert(nrows == ncols);
    for (int i = 0; i < nrows; ++i) {
        for (int j = i; j < ncols; ++j) {
            is >> d[i][j];
            d[j][i] = d[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.nrows; ++i) {
        for (int j = 0; j < matrix.ncols; ++j) {
            os << matrix.d[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (int i = 0; i < matrix.nrows; ++i) {
        for (int j = 0; j < matrix.ncols; ++j) {
            is >> matrix.d[i][j];
        }
    }
    return is;
}

Matrix call_dgemm(const Matrix &matA, const Matrix &matB) {
    assert(matA.ncols == matB.nrows);

    // std::ostringstream oss;
    // oss << "MatMul, (" << matA.nrows << "," << matA.ncols << ") *";
    // oss << " (" << matB.nrows << "," << matB.ncols << ")";
    // Timer::tick("BLAS", oss.str());

    Matrix result = Matrix(matA.nrows, matB.ncols);
    cblas_dgemm(
        CblasRowMajor,  // Row major layout
        CblasNoTrans,   // Do not transpose A
        CblasNoTrans,   // Do not transpose B
        result.nrows,   // Rows of result
        result.ncols,   // Columns of result
        matA.ncols,     // Shared dim of A and B
        1.0,            // No alpha scaling
        *matA.d,        // Data of matA
        matA.ncols,     // Columns of matA
        *matB.d,        // Data of B
        matB.ncols,     // Columns of matB
        0.0,            // Set beta to 0
        result.d[0],      // Data of result
        result.ncols    // Columns of result
    );
    // Timer::tick("BLAS", oss.str());
    return result;    
}

int call_dsyev(const Matrix &mat, double* eigval) {
    assert (mat.ncols == mat.nrows);

    // std::ostringstream oss;
    // oss << "Eigval, (" << mat.nrows << "," << mat.ncols << ")";
    // Timer::tick("LAPACK", oss.str());

    int lda = mat.nrows ;

    int info = LAPACKE_dsyev(
        LAPACK_ROW_MAJOR,   // Row major layout
        'V',                // Compute eigenvalues and eigenvectors
        'U',                // Upper triangle is stored
        mat.nrows,          // The order of mat
        mat.d[0],           // Data
        lda,                // Leading dim of mat
        eigval              // Results of eigen values
    );
    if (info != 0) {
        std::cerr << "Failed to diagonalize matrix" << std::endl;
        return 1;
    }

    // Timer::tick("LAPACK", oss.str());
    return info;
}