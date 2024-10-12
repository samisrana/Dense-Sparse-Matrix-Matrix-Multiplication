#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include <vector>

// Function to generate a dense matrix of given size (rows x cols) with random integers
std::vector<std::vector<int>> generate_dense_matrix(int rows, int cols);

// Function to generate a sparse matrix of given size (rows x cols) with a specified sparsity percentage
std::vector<std::vector<int>> generate_sparse_matrix(int rows, int cols, double sparsity);

#endif // MATRIX_GENERATOR_H
