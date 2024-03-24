#include "Matrix.h"
#include "MatrixReader.h"
#include <iostream>

int main() {
    // Test matrix initialization
    Matrix mat(3, 4);
    std::cout << mat;

    // Test matrix reader 
    MatrixReader mat_reader;
    mat_reader.init("test.in");
    std::cout << mat_reader;
    return 0;
}