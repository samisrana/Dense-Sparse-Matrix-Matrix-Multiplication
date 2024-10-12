#include "matrix/multiplication.h"
#include "optimizations/simd_optimization.h"
#include "optimizations/cache_optimization.h"
#include <stdexcept>  // For std::invalid_argument
#include <thread>     // For multi-threading
#include <functional> // For std::function
#include <algorithm>  // For std::min

// Matrix multiplication function with configurable optimizations
std::vector<std::vector<int>> matrix_multiplication(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    bool use_multithreading,
    bool use_simd,
    bool use_cache_optimization,
    int num_threads) {

    // Check if multiplication is valid
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Number of columns in A must match the number of rows in B");
    }

    // Initialize the result matrix C
    std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));

    // Lambda function to select and apply the appropriate optimization
std::function<void(int, int)> multiply_func = [&](int start_row, int end_row) {
    if (use_cache_optimization && use_simd) {
        multiply_block_simd(A, B, C, start_row, end_row, 64);
    } else if (use_cache_optimization) {
        multiply_block_cache(A, B, C, start_row, end_row, 64);
    } else if (use_simd) {
        multiply_block_simd(A, B, C, start_row, end_row, 64);
    } else {
        multiply_standard(A, B, C, start_row, end_row);  // Use standard multiplication
    }
};    // Multi-threaded execution
    if (use_multithreading && num_threads > 1) {
        // Ensure the number of threads does not exceed the number of rows
        num_threads = std::min(num_threads, rowsA);

        std::vector<std::thread> threads;
        int rows_per_thread = rowsA / num_threads;
        int remaining_rows = rowsA % num_threads;

        int start_row = 0;
        for (int t = 0; t < num_threads; ++t) {
            int end_row = start_row + rows_per_thread + (t < remaining_rows ? 1 : 0);
            threads.emplace_back(multiply_func, start_row, end_row);
            start_row = end_row;
        }

        // Wait for all threads to finish
        for (auto& th : threads) {
            th.join();
        }
    } else {
        // Single-threaded execution
        multiply_func(0, rowsA);
    }

    return C;
}
