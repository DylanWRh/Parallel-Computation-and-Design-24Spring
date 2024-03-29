#include "Matrix.h"
#include "MatrixReader.h"
#include "Timer.h"
#include <iostream>

int main() {
    // Test matrix initialization
    Matrix mat(3000, 4000);
    Matrix mat2(4000, 3000);
    // std::cout << mat;

    // Test matrix reader 
    MatrixReader mat_reader;
    mat_reader.init("test.in");
    std::cout << mat_reader;

    // Show timer information
    Timer::show_info();
    return 0;
}