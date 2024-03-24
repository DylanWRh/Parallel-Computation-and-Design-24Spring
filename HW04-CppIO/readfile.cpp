#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype> 
#include <sstream>
#include <cstring>

std::string s_to_lower(const std::string& s);
void trim(std::string &s);
int compare_str(const std::string& s1, const std::string& s2);

class Matrix {
public:
    std::string calculation;
    std::string matrix_type;
    int matrix_print;
    int nrows;
    int ncols;

    Matrix(){};

    int assign_vars(const std::string& var_name, const std::string& var_val);
    int readfile(std::string filename);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

int main() {
    Matrix test_mat = Matrix();
    std::string filename = "test.in";
    if (test_mat.readfile(filename)) {
        std::cerr << "Failed to read in the matrix." << std::endl;
    }
    else {
        std::cout << test_mat;
    }
    return 0;
}

std::string s_to_lower(const std::string& s) {
    std::string s_lower = s;
    std::transform(
        s_lower.begin(), s_lower.end(), s_lower.begin(),
        [](char c) {return std::tolower(c);}
    );
    return s_lower;
}

void trim(std::string &s){
    static const char whitespace[] = " \n\t\v\r\f";
    s.erase(0, s.find_first_not_of(whitespace));
    s.erase(s.find_last_not_of(whitespace) + 1U);
}

int compare_str(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length())
        return 0; 
    
    std::string s1_lower = s_to_lower(s1);
    std::string s2_lower = s_to_lower(s2);

    return (s1_lower == s2_lower);
}

int Matrix::assign_vars(const std::string& var_name, const std::string& var_val) {
    if (compare_str(var_name, "calculation")) {
        calculation = var_val;
    }
    else if (compare_str(var_name, "matrix_type")) {
        std::cout << var_val;
        matrix_type = var_val;
    }
    else if (compare_str(var_name, "matrix_print")) {
        try {
            matrix_print = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1; 
        }
    } 
    else if (compare_str(var_name, "nrows")) {
        try {
            nrows = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1; 
        }
    } 
    else if (compare_str(var_name, "ncols")) {
        try {
            ncols = std::stoi(var_val);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1; // indicate failure
        }
    } 
    else {
        std::cerr << "Error: Unknown variable name" << std::endl;
        return -1;
    }
    return 0;
}

int Matrix::readfile(std::string filename) {
    std::ifstream f(filename);

    if (! f.is_open()) {
        std::cerr << "Unable to open input file." << std::endl;
        return 1;
    } 

    std::string line;
    while (std::getline(f, line)) {

        trim(line);
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string var_name, var_val;
        iss >> var_name >> var_val;

        if (this->assign_vars(var_name, s_to_lower(var_val))) {
            return 1;
        }
    }

    f.close();

    return 0;
}

std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
    os << "Calculation: " << matrix.calculation << std::endl;
    os << "Matrix Type: " << matrix.matrix_type << std::endl;
    os << "Matrix Print: " << matrix.matrix_print << std::endl;
    os << "Number of Rows: " << matrix.nrows << std::endl;
    os << "Number of Cols: " << matrix.ncols << std::endl;
    return os;
}

