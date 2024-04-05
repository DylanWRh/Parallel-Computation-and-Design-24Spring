#include "Matrix.h"
#include "MatrixReader.h"
#include "Timer.h"
#include <iostream>
#include <fstream>

int main() {
    Matrix mat3_1(3, 3);
    {    
        std::ifstream file("./test/mat3_1.in");
        if (!file) {
            std::cerr << "Failed to open the file mat3_1.in." << std::endl;
            return 1;
        }
        file >> mat3_1;
        file.close();
    }

    Matrix mat3_2(3, 3);
    {    
        std::ifstream file("./test/mat3_2.in");
        if (!file) {
            std::cerr << "Failed to open the file mat3_2.in." << std::endl;
            return 1;
        }
        file >> mat3_2;
        file.close();
    }

    Matrix res3 = mat3_1 * mat3_2;
    {
        std::ofstream file("./test/mat3.out");
        if (!file) {
            std::cerr << "Failed to write file mat3.out." << std::endl;
            return 1;
        }
        file << res3;
        file.close();
    }

    Matrix res3_blas = call_dgemm(mat3_1, mat3_2);
    {
        std::ofstream file("./test/mat3_blas.out");
        if (!file) {
            std::cerr << "Failed to write file mat3_blas.out." << std::endl;
            return 1;
        }
        file << res3_blas;
        file.close();
    }

    Matrix mat100_1(100, 100);
    {    
        std::ifstream file("./test/mat100_1.in");
        if (!file) {
            std::cerr << "Failed to open the file mat100_1.in." << std::endl;
            return 1;
        }
        file >> mat100_1;
        file.close();
    }

    Matrix mat100_2(100, 100);
    {    
        std::ifstream file("./test/mat100_2.in");
        if (!file) {
            std::cerr << "Failed to open the file mat100_2.in." << std::endl;
            return 1;
        }
        file >> mat100_2;
        file.close();
    }

    Matrix res100 = mat100_1 * mat100_2;
    {
        std::ofstream file("./test/mat100.out");
        if (!file) {
            std::cerr << "Failed to write file mat100.out." << std::endl;
            return 1;
        }
        file << res100;
        file.close();
    }

    Matrix res100_blas = call_dgemm(mat100_1, mat100_2);
    {
        std::ofstream file("./test/mat100_blas.out");
        if (!file) {
            std::cerr << "Failed to write file mat100_blas.out." << std::endl;
            return 1;
        }
        file << res100_blas;
        file.close();
    }

    Matrix mat1000_1(1000, 1000);
    {    
        std::ifstream file("./test/mat1000_1.in");
        if (!file) {
            std::cerr << "Failed to open the file mat1000_1.in." << std::endl;
            return 1;
        }
        file >> mat1000_1;
        file.close();
    }

    Matrix mat1000_2(1000, 1000);
    {    
        std::ifstream file("./test/mat1000_2.in");
        if (!file) {
            std::cerr << "Failed to open the file mat1000_2.in." << std::endl;
            return 1;
        }
        file >> mat1000_2;
        file.close();
    }

    Matrix res1000 = mat1000_1 * mat1000_2;
    {
        std::ofstream file("./test/mat1000.out");
        if (!file) {
            std::cerr << "Failed to write file mat1000.out." << std::endl;
            return 1;
        }
        file << res1000;
        file.close();
    }

    Matrix res1000_blas = call_dgemm(mat1000_1, mat1000_2);
    {
        std::ofstream file("./test/mat1000_blas.out");
        if (!file) {
            std::cerr << "Failed to write file mat1000_blas.out." << std::endl;
            return 1;
        }
        file << res1000_blas;
        file.close();
    }

    Timer::show_info();
    return 0;
}
