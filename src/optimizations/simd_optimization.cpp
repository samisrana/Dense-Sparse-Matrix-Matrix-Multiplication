#include "optimizations/simd_optimization.h"
#include <immintrin.h>
#include <algorithm>
#include <omp.h>         // Optional: OpenMP for parallelization

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

    // Optional: Parallelize outer loop using OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < colsB; j += block_size) {

            // Initialize a temporary SIMD sum accumulator
            __m256i sum = _mm256_setzero_si256();

            for (int k = 0; k < colsA; k += 8) {  // Process 8 elements at a time
                // Load A[i][k] into all elements of a SIMD register
                __m256i vecA = _mm256_set1_epi32(A[i][k]);

                // Load 8 elements from B[k][j] to B[k][j+7] (unaligned load)
                __m256i vecB = _mm256_loadu_si256((__m256i*)&B[k][j]);

                // Perform element-wise multiplication: vecA * vecB
                __m256i product = _mm256_mullo_epi32(vecA, vecB);

                // Accumulate the results
                sum = _mm256_add_epi32(sum, product);
            }

            // Store the accumulated SIMD sum into a temporary array
            alignas(32) int temp[8];
            _mm256_store_si256((__m256i*)temp, sum);

            // Add the temporary array to the final matrix C
            for (int jj = 0; jj < block_size && (j + jj) < colsB; ++jj) {
                C[i][j + jj] += temp[jj];
            }
        }
    }
}
