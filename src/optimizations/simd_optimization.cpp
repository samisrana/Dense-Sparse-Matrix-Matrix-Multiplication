#include "optimizations/simd_optimization.h"
#include <immintrin.h>
#include <algorithm>

// Standard matrix multiplication
void multiply_standard(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row) {

    int colsB = B[0].size();
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (size_t k = 0; k < A[0].size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// SIMD-optimized matrix multiplication with cache blocking
void multiply_block_simd(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    std::vector<std::vector<int>>& C,
    int start_row, int end_row, int block_size) {

    int colsB = B[0].size();
    int colsA = A[0].size();

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < colsB; j += block_size) {
            for (int k = 0; k < colsA; k += 8) {  // Process 8 elements at a time
                __m256i sum = _mm256_setzero_si256();

                for (int kk = k; kk < std::min(k + 8, colsA); ++kk) {
                    // Load A[i][kk] into all elements of a SIMD register
                    __m256i vecA = _mm256_set1_epi32(A[i][kk]);

                    // Load 8 elements from B[kk][j .. j+7]
                    __m256i vecB = _mm256_loadu_si256((__m256i*)&B[kk][j]);

                    // Perform element-wise multiplication
                    __m256i product = _mm256_mullo_epi32(vecA, vecB);

                    // Accumulate the results
                    sum = _mm256_add_epi32(sum, product);
                }

                // Store the SIMD sum into a temporary array
                int temp[8];
                _mm256_storeu_si256((__m256i*)temp, sum);

                // Accumulate the results into the output matrix C
                for (int jj = 0; jj < 8 && (j + jj) < colsB; ++jj) {
                    C[i][j + jj] += temp[jj];
                }
            }
        }
    }
}
