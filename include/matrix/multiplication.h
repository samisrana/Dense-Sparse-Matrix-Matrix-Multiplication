#ifndef MULTIPLICATION_H
#define _MULTIPLICATION_H

#include <vector>

// Structure for compressed sparse row representation of a sparse matrix
struct SparseMatrix {
    std::vector<int> nonzeroValues;
    std::vector<int> rowPtr;
    std::vector<int> colIndex;
};

// Function declarations
std::vector<std::vector<int>> dense_dense_multiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);
std::vector<std::vector<int>> dense_sparse_multiplication(const std::vector<std::vector<int>>& A, const SparseMatrix& B, int n);
SparseMatrix sparse_sparse_multiplication(const SparseMatrix& A, const SparseMatrix& B, int n);

#endif // MULTIPLICATION_H
