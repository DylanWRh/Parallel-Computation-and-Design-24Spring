import numpy as np
import os

def generate_and_save_matrix(filename, rows, cols):
    matrix1 = np.random.randn(rows, cols) 
    np.savetxt(filename + '_1', matrix1, fmt='%f') 
    matrix2 = np.random.randn(rows, cols) 
    np.savetxt(filename + '_2', matrix2, fmt='%f') 
    np.savetxt(filename + '_ref', matrix1 + matrix2, fmt='%f') 

def generate_and_save_matrix_complex(filename, rows, cols):
    matrix1_real = np.random.randn(rows, cols) 
    matrix1_imag = np.random.randn(rows, cols)
    with open(filename + '_1', 'w') as f:
        for i in range(rows):
            for j in range(cols):
                f.write(f"({matrix1_real[i, j]},{matrix1_imag[i, j]}) ")
            f.write('\n')
    matrix2_real = np.random.randn(rows, cols)
    matrix2_imag = np.random.randn(rows, cols)
    with open(filename + '_2', 'w') as f:
        for i in range(rows):
            for j in range(cols):
                f.write(f"({matrix2_real[i, j]},{matrix2_imag[i, j]}) ")
            f.write('\n')
    matrix_ref_real = matrix1_real + matrix2_real
    matrix_ref_imag = matrix1_imag + matrix2_imag
    with open(filename + '_ref', 'w') as f:
        for i in range(rows):
            for j in range(cols):
                f.write(f"({matrix_ref_real[i, j]},{matrix_ref_imag[i, j]}) ")
            f.write('\n')
def main():
    ns = [3, 3, 3, 100, 100, 100]
    ms = [3, 100, 500, 3, 100, 500]

    test_cases = [
        {'filename': f'mat_{i}_{j}', 'rows': i, 'cols': j}
        for i, j in zip(ns, ms)
    ]

    if not os.path.exists("test"):
        os.makedirs("test")

    for case in test_cases:
        generate_and_save_matrix(os.path.join("test", case["filename"]), case["rows"], case["cols"])

    print("Double test cases generated successfully.")

    if not os.path.exists("test_complex"):
        os.makedirs("test_complex")

    for case in test_cases:
        generate_and_save_matrix_complex(os.path.join("test_complex", case["filename"]), case["rows"], case["cols"])
    
    print("Complex test cases generated successfully.")

if __name__ == "__main__":
    main()
