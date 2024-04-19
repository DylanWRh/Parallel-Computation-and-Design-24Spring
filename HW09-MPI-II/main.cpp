#include "Matrix.h"

#ifdef __MPI
#include <mpi.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int test_matadd(int nrow, int ncol, 
                std::string filename1, 
                std::string filename2,
                std::string filename_out) {

    Matrix mat1;
    Matrix mat2;
    Matrix result;

#ifdef __MPI
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rows_per_proc = nrow / (size - 1);
    int rows_left = nrow % (size - 1);

    if (rank == 0) {
        result = Matrix(nrow, ncol);
        mat1 = Matrix(nrow, ncol);
        mat2 = Matrix(nrow, ncol);
    }
   
    if (rank == 0) {
        std::ifstream file(filename1);
        if (!file) {
            std::cerr << "Failed to open the file " << filename1 << std::endl;
            return 1;
        }
        file >> mat1;
        file.close();
    } 

    if (rank == 0) {
        std::ifstream file(filename2);
        if (!file) {
            std::cerr << "Failed to open the file " << filename2 << std::endl;
            return 1;
        }
        file >> mat2;
        file.close();
    } 

    int tag_mat1 = 0, tag_mat2 = 1, tag_res = 2;

    if (rank == 0) {
        MPI_Request* req_send1_all = new MPI_Request[size - 1];
        MPI_Request* req_send2_all = new MPI_Request[size - 1];
        MPI_Request* req_recv_all = new MPI_Request[size - 1];

        int cur_row = 0;
        for (int i = 1; i < size; i++) {
            double* buf = mat1.d[cur_row];
            int rows_send = rows_per_proc + (i <= rows_left);
            MPI_Isend(
                buf, rows_send * ncol, MPI_DOUBLE, 
                i, tag_mat1, MPI_COMM_WORLD, &req_send1_all[i-1]);
            
            cur_row += rows_send;
        }

        cur_row = 0;
        for (int i = 1; i < size; i++) {
            double* buf = mat2.d[cur_row];
            int rows_send = rows_per_proc + (i <= rows_left);
            MPI_Isend(
                buf, rows_send * ncol, MPI_DOUBLE, 
                i, tag_mat2, MPI_COMM_WORLD, &req_send2_all[i-1]);
            cur_row += rows_send;
        }
        
        cur_row = 0;
        for (int i = 1; i < size; i++) {
            double* buf = result.d[cur_row];
            int rows_recv = rows_per_proc + (i <= rows_left);
            
            MPI_Irecv(
                buf, rows_recv * ncol, MPI_DOUBLE, 
                i, tag_res, MPI_COMM_WORLD, &req_recv_all[i-1]);
            cur_row += rows_recv;
        }

        for (int i = 0; i < size - 1; i++) {
            MPI_Wait(&req_send1_all[i], MPI_STATUS_IGNORE);
            MPI_Wait(&req_send2_all[i], MPI_STATUS_IGNORE);
            MPI_Wait(&req_recv_all[i], MPI_STATUS_IGNORE);
        }
        
        delete [] req_send1_all;
        delete [] req_send2_all;
        delete [] req_recv_all;
    } else {
        MPI_Request req_recv1;
        MPI_Request req_recv2;
        MPI_Request req_send;

        int rows_recv = rows_per_proc + (rank <= rows_left);

        mat1 = Matrix(rows_recv, ncol);
        MPI_Irecv(
            mat1.d[0], rows_recv * ncol, MPI_DOUBLE, 
            0, tag_mat1, MPI_COMM_WORLD, &req_recv1);
        
        mat2 = Matrix(rows_recv, ncol);
        MPI_Irecv(
            mat2.d[0], rows_recv * ncol, MPI_DOUBLE, 
            0, tag_mat2, MPI_COMM_WORLD, &req_recv2);

        MPI_Wait(&req_recv1, MPI_STATUS_IGNORE);
        MPI_Wait(&req_recv2, MPI_STATUS_IGNORE);
        
        result = Matrix(rows_recv, ncol);
        result = mat1 + mat2;
                
        MPI_Isend(
            result.d[0], rows_recv * ncol, MPI_DOUBLE, 
            0, tag_res, MPI_COMM_WORLD, &req_send);
        
        MPI_Wait(&req_send, MPI_STATUS_IGNORE);
    }

    if (rank == 0) {
        std::ofstream file(filename_out);
        if (!file) {
            std::cerr << "Failed to write in the file " << filename_out << std::endl;
            return 1;
        }
        file << result;
        file.close();
    }
    

#endif


    return 0;
}
int main() {

#ifdef __MPI
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size == 1) {
        std::cerr << "Need at least 2 processes" << std::endl;
        return 1;
    }

    test_matadd(
        3, 3, 
        "./test/mat_3_3_1",
        "./test/mat_3_3_2",
        "./test/mat_3_3_out"
    );
    MPI_Barrier(MPI_COMM_WORLD);

    test_matadd(
        3, 100, 
        "./test/mat_3_100_1",
        "./test/mat_3_100_2",
        "./test/mat_3_100_out"
    );
    MPI_Barrier(MPI_COMM_WORLD);  

    test_matadd(
        3, 500, 
        "./test/mat_3_500_1",
        "./test/mat_3_500_2",
        "./test/mat_3_500_out"
    );
    MPI_Barrier(MPI_COMM_WORLD);  

    test_matadd(
        100, 3, 
        "./test/mat_100_3_1",
        "./test/mat_100_3_2",
        "./test/mat_100_3_out"
    );
    MPI_Barrier(MPI_COMM_WORLD); 

    test_matadd(
        100, 100, 
        "./test/mat_100_100_1",
        "./test/mat_100_100_2",
        "./test/mat_100_100_out"
    );
    MPI_Barrier(MPI_COMM_WORLD); 

    test_matadd(
        100, 500, 
        "./test/mat_100_500_1",
        "./test/mat_100_500_2",
        "./test/mat_100_500_out"
    );
    MPI_Barrier(MPI_COMM_WORLD); 

    MPI_Finalize();
#endif

    return 0;
}
