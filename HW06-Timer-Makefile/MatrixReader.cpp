#include "MatrixReader.h"
#include "StringUtils.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>

MatrixReader::MatrixReader() {}

MatrixReader::~MatrixReader() {}

void MatrixReader::init(const std::string &filename) {
    Timer::tick("MatrixReader", "init");
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }
    read(f);
    f.close();
    Timer::tick("MatrixReader", "init");
}

void MatrixReader::read(std::ifstream& f) {
    Timer::tick("MatrixReader", "read");
    std::string line;
    while (std::getline(f, line)) {
        StringUtils::trim(line);
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string var_name, var_val;
        iss >> var_name >> var_val;

        assign_vars(var_name, StringUtils::s_to_lower(var_val));
    }
    f.close();
    Timer::tick("MatrixReader", "read");
}

void MatrixReader::assign_vars(const std::string& var_name, const std::string& var_val) {
    if (StringUtils::compare_str(var_name, "calculation")) {
        calculation = var_val;
    }
    else if (StringUtils::compare_str(var_name, "matrix_type")) {
        matrix_type = var_val;
    }
    else if (StringUtils::compare_str(var_name, "matrix_print")) {
        try {
            matrix_print = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } 
    else if (StringUtils::compare_str(var_name, "nrows")) {
        try {
            nrows = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } 
    else if (StringUtils::compare_str(var_name, "ncols")) {
        try {
            ncols = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } 
    else {
        std::cerr << "Error: Unknown variable name" << std::endl;
    }
}

std::ostream& operator<< (std::ostream& os, const MatrixReader& mat) {
    os << "Calculation: " << mat.calculation << std::endl;
    os << "Matrix Type: " << mat.matrix_type << std::endl;
    os << "Matrix Print: " << mat.matrix_print << std::endl;
    os << "Number of Rows: " << mat.nrows << std::endl;
    os << "Number of Cols: " << mat.ncols << std::endl;
    return os;
}

