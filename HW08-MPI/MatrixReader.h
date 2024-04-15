#ifndef MAT_READER_H
#define MAT_READER_H

#include <string>
#include <iostream>
#include <fstream>

class MatrixReader{
public:
    MatrixReader();
    ~MatrixReader();

    std::string calculation;
    std::string matrix_type;
    int matrix_print;
    int nrows;
    int ncols;
    
    void init(const std::string &filename);
    friend std::ostream& operator<<(std::ostream& os, const MatrixReader& mat);
private:
    void read(std::ifstream& file);
    void assign_vars(const std::string& var_name, const std::string& var_val);
};

#endif