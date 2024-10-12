#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <vector> //vector data structure for dynamically resizable arrays, used to represent matrices

// Function declaration for matrix multiplication with configurable optimizations
std::vector<std::vector<int>> matrix_multiplication(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    bool use_multithreading = false,
    bool use_simd = false,
    bool use_cache_optimization = false,
    int num_threads = 1);

#endif // MULTIPLICATION_H
