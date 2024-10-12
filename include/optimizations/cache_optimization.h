#ifndef CACHE_OPTIMIZATION_H
#define CACHE_OPTIMIZATION_H

#include <vector>

// Function for cache-optimized matrix multiplication
void multiply_block_cache(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row, int block_size);

#endif

