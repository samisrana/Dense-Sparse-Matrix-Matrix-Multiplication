#include "optimizations/cache_optimization.h"
#include <algorithm>

void multiply_block_cache(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row, int block_size) {

    int n = B[0].size();

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < n; j += block_size) {
            for (int k = 0; k < n; k += block_size) {
                // Process smaller blocks within the larger matrix
                for (int ii = i; ii < std::min(i + block_size, end_row); ++ii) {
                    for (int jj = j; jj < std::min(j + block_size, n); ++jj) {
                        int sum = 0;
                        for (int kk = k; kk < std::min(k + block_size, n); ++kk) {
                            sum += A[ii][kk] * B[kk][jj];
                        }
                        C[ii][jj] += sum;
                    }
                }
            }
        }
    }
}

