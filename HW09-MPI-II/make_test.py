import numpy as np
import os

def generate_and_save_matrix(filename, rows, cols):
    matrix1 = np.random.randn(rows, cols) 
    np.savetxt(filename + '_1', matrix1, fmt='%f') 
    matrix2 = np.random.randn(rows, cols) 
    np.savetxt(filename + '_2', matrix2, fmt='%f') 
    np.savetxt(filename + '_ref', matrix1 + matrix2, fmt='%f') 

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

    print("Test cases generated successfully.")

if __name__ == "__main__":
    main()
