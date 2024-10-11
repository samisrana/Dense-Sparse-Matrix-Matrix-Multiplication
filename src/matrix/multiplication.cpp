#include "matrix/multiplication.h"
#include <stdexcept>

// native matrix multiplication for matrices
std::vector<std::vector<int>> matrix_multiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    // Check if multiplication is valid, number of columns in matrix A must match the number of rows in matrix B
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Number of columns in A must match the number of rows in B"); //throw exception
    }

    // Initialize the result matrix C with dimensions (rowsA x colsB), filled with 0s
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}
