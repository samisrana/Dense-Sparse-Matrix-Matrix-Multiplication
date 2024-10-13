#include "optimizations/cache_optimization.h"
#include <algorithm>  

void multiply_block_cache(const std::vector<std::vector<int>>& A,
                          const std::vector<std::vector<int>>& B,
                          std::vector<std::vector<int>>& C,
                          int block_size) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    for (int ii = 0; ii < rowsA; ii += block_size) {
        for (int jj = 0; jj < colsB; jj += block_size) {
            for (int kk = 0; kk < colsA; kk += block_size) {
                // Block multiplication
                for (int i = ii; i < std::min(ii + block_size, rowsA); ++i) {
                    for (int j = jj; j < std::min(jj + block_size, colsB); ++j) {
                        int sum = 0;
                        for (int k = kk; k < std::min(kk + block_size, colsA); ++k) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
}
