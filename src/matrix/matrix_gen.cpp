#include "matrix/matrix_gen.h"
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

// Initialize random seed (call this once in main program)
void initialize_random_seed() {
    std::srand(std::time(0));
}

// Function to generate a dense matrix of given size (rows x cols) with random numbers
std::vector<std::vector<int>> generate_dense_matrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = std::rand() % 100; // Random integer between 0 and 99
        }
    }
    return matrix;
}

// Function to generate a sparse matrix with a specified sparsity percentage
std::vector<std::vector<int>> generate_sparse_matrix(int rows, int cols, double sparsity) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));

    int total_elements = rows * cols;
    int non_zero_elements = static_cast<int>(total_elements * (1.0 - sparsity));

    // Generate a list of random positions where non-zero values will be placed
    std::vector<int> positions(total_elements);
    for (int i = 0; i < total_elements; ++i) {
        positions[i] = i;
    }
    std::shuffle(positions.begin(), positions.end(), std::default_random_engine(std::rand()));

    // Place random non-zero values at the selected positions
    for (int i = 0; i < non_zero_elements; ++i) {
        int pos = positions[i];
        int row = pos / cols;
        int col = pos % cols;
        matrix[row][col] = std::rand() % 100 + 1; // Non-zero value between 1 and 100
    }

    return matrix;
}

