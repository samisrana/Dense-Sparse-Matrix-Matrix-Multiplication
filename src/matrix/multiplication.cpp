#include "matrix/multiplication.h"

// Dense-Dense matrix multiplication
std::vector<std::vector<int>> dense_dense_multiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size(); // assuming A and B are square matrices
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Dense-Sparse matrix multiplication (assuming B is sparse in CSR format)
std::vector<std::vector<int>> dense_sparse_multiplication(const std::vector<std::vector<int>>& A, const SparseMatrix& B, int n) {
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = B.rowPtr[i]; j < B.rowPtr[i + 1]; ++j) {
            int col = B.colIndex[j];
            int value = B.nonzeroValues[j];
            for (int k = 0; k < n; ++k) {
                C[i][k] += A[i][col] * value;
            }
        }
    }

    return C;
}

// Sparse-Sparse matrix multiplication (both A and B are sparse in CSR format)
SparseMatrix sparse_sparse_multiplication(const SparseMatrix& A, const SparseMatrix& B, int n) {
    SparseMatrix C;
    C.rowPtr.push_back(0);

    for (int i = 0; i < n; ++i) {
        std::vector<int> row(n, 0);  // to hold intermediate row results

        for (int j = A.rowPtr[i]; j < A.rowPtr[i + 1]; ++j) {
            int colA = A.colIndex[j];
            int valueA = A.nonzeroValues[j];

            for (int k = B.rowPtr[colA]; k < B.rowPtr[colA + 1]; ++k) {
                int colB = B.colIndex[k];
                int valueB = B.nonzeroValues[k];
                row[colB] += valueA * valueB;
            }
        }

        for (int j = 0; j < n; ++j) {
            if (row[j] != 0) {
                C.nonzeroValues.push_back(row[j]);
                C.colIndex.push_back(j);
            }
        }

        C.rowPtr.push_back(C.nonzeroValues.size());
    }

    return C;
}
