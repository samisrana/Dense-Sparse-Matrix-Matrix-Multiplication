#include "matrix/multiplication.h"
#include <iostream>

// Helper function to print matrices
void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Helper function to print CSR matrix
void print_csr_matrix(const SparseMatrix& matrix, int rows) {
    std::cout << "Values: ";
    for (const auto& value : matrix.nonzeroValues) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Column Indices: ";
    for (const auto& col : matrix.colIndex) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    std::cout << "Row Pointers: ";
    for (const auto& rowPtr : matrix.rowPtr) {
        std::cout << rowPtr << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Simple test case for dense-dense matrix multiplication
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}}; //matrix 1
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}}; //matrix 2
    std::vector<std::vector<int>> C = dense_dense_multiplication(A, B); //product 

    std::cout << "Dense-Dense Multiplication Result:" << std::endl;
    print_matrix(C);

    // Dense-Sparse Multiplication (Assuming matrix B is sparse)
    SparseMatrix sparse_B;
    sparse_B.nonzeroValues = {5, 7};
    sparse_B.colIndex = {0, 1};
    sparse_B.rowPtr = {0, 1, 2};

    std::vector<std::vector<int>> D = dense_sparse_multiplication(A, sparse_B, 2);

    std::cout << "\nDense-Sparse Multiplication Result:" << std::endl;
    print_matrix(D);

    // Sparse-Sparse Multiplication
    SparseMatrix sparse_A;
    sparse_A.nonzeroValues = {1, 3};
    sparse_A.colIndex = {0, 1};
    sparse_A.rowPtr = {0, 1, 2};

    SparseMatrix result_sparse_sparse = sparse_sparse_multiplication(sparse_A, sparse_B, 2);

    std::cout << "\nSparse-Sparse Multiplication Result (CSR Format):" << std::endl;
    print_csr_matrix(result_sparse_sparse, 2);

    return 0;
}
