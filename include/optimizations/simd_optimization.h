#ifndef SIMD_OPTIMIZATION_H
#define SIMD_OPTIMIZATION_H

#include <vector>

// Standard matrix multiplication
void multiply_standard(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row);

// SIMD-optimized matrix multiplication
void multiply_block_simd(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row, int block_size);

#endif
