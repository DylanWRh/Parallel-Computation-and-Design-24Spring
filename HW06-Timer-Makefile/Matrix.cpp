#include "Matrix.h"
#include "Timer.h"
#include <limits>
#include <stdexcept>

Matrix::Matrix() {}
Matrix::Matrix(const int &nrows_, const int &ncols_, const bool flag_zero) : nrows(nrows_), ncols(ncols_) {
    d = new double*[nrows];
    for (int i = 0; i < nrows; ++i) {
        d[i] = new double[ncols];
    }
    if (flag_zero) {
        set_zero();
    }
}
Matrix::~Matrix() {
    for (int i = 0; i < nrows; ++i) {
        delete[] d[i];
    }
    delete[] d;
}

void Matrix::set_zero() {
    Timer::tick("Matrix", "set_zero()");
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            d[i][j] = 0.0;
        }
    }
    Timer::tick("Matrix", "set_zero()");
}

void Matrix::set_zero(const int &nrows_, const int &ncols_) {
    Timer::tick("Matrix", "set_zero(const int &, const int &)");
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
    Timer::tick("Matrix", "set_zero(const int &, const int &)");
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
