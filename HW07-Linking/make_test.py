import numpy as np
import os

def generate_and_save_matrix(filename, rows, cols):
    matrix = np.random.randint(1, 10, size=(rows, cols)) 
    np.savetxt(filename, matrix, fmt='%d') 

def main():
    test_cases = [
        {"filename": "mat3_1.in", "rows": 3, "cols": 3},
        {"filename": "mat3_2.in", "rows": 3, "cols": 3},
        {"filename": "mat100_1.in", "rows": 100, "cols": 100},
        {"filename": "mat100_2.in", "rows": 100, "cols": 100},
        {"filename": "mat1000_1.in", "rows": 1000, "cols": 1000},
        {"filename": "mat1000_2.in", "rows": 1000, "cols": 1000}
    ]

    if not os.path.exists("test"):
        os.makedirs("test")

    for case in test_cases:
        generate_and_save_matrix(os.path.join("test", case["filename"]), case["rows"], case["cols"])

    print("Test cases generated successfully.")

if __name__ == "__main__":
    main()
