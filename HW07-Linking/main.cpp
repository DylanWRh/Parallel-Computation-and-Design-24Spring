#include "Matrix.h"
#include "MatrixReader.h"
#include "Timer.h"
#include <iostream>
#include <fstream>

int test_matmul(int nrow1, int ncol1, int nrow2, int ncol2, 
                std::string filename1, std::string filename2,
                std::string filename_out, std::string filename_out_blas) {

    Matrix mat1(nrow1, ncol1);
    Matrix mat2(nrow2, ncol2);

    {
        std::ifstream file(filename1);
        if (!file) {
            std::cerr << "Failed to open the file " << filename1 << std::endl;
            return 1;
        }
        file >> mat1;
        file.close();
    }

    {
        std::ifstream file(filename2);
        if (!file) {
            std::cerr << "Failed to open the file " << filename2 << std::endl;
            return 1;
        }
        file >> mat2;
        file.close();
    }
    
    Matrix result = mat1 * mat2;
    {
        std::ofstream file(filename_out);
        if (!file) {
            std::cerr << "Failed to write file " << filename_out << std::endl;
            return 1;
        }
        file << result;
        file.close();
    }

    result = call_dgemm(mat1, mat2);
    {
        std::ofstream file(filename_out_blas);
        if (!file) {
            std::cerr << "Failed to write file " << filename_out_blas << std::endl;
            return 1;
        }
        file << result;
        file.close();
    }

    return 0;
}

int test_eigval(int nrows, std::string filename, std::string filename_out) {
    Matrix mat(nrows, nrows);
    {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Failed to open the file " << filename << std::endl;
            return 1;
        }
        // file >> mat;
        mat.read_symm(file);
        file.close();
    }

    double *n = new double[nrows];
    call_dsyev(mat, n);

    {
        std::ofstream file(filename_out);
        if (!file) {
            std::cerr << "Failed to write file " << filename_out << std::endl;
            return 1;
        }
        file << "Eigenvalues:" << std::endl;
        for (int i = 0; i < nrows; ++i) {
            file << n[i] << std::endl;
        }

        file << std::endl << "Eigenvalues" << std::endl;
        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < nrows; ++j) {
                int index = i * nrows + j;
                file << mat.d[0][index] << " ";
            }
            file << std::endl;
        }
        file.close();
    }
    return 0;
}

int main() {
    test_matmul(
        3, 3, 3, 3, "./test/mat3_1.in", "./test/mat3_2.in",
        "./test/mat3.out", "./test/mat3_blas.out"
    );
    test_matmul(
        100, 100, 100, 100, "./test/mat100_1.in", "./test/mat100_2.in",
        "./test/mat100.out", "./test/mat100_blas.out"
    );
    test_matmul(
        1000, 1000, 1000, 1000, "./test/mat1000_1.in", "./test/mat1000_2.in",
        "./test/mat1000.out", "./test/mat1000_blas.out"
    );

    test_eigval(3, "./test/sym3.in", "./test/sym3.out");
    test_eigval(100, "./test/sym100.in", "./test/sym100.out");
    test_eigval(1000, "./test/sym1000.in", "./test/sym1000.out");

    Timer::show_info();
    return 0;
}
