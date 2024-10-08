#include "matrix/multiplication.h"
#include <iostream>

int main() {
    // Simple test case for dense-dense matrix multiplication
    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}}; //matrix 1
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}}; //matrix 2
    std::vector<std::vector<int>> C = dense_dense_multiplication(A, B); //product 

    // Print result of dense-dense multiplication
    for (auto row : C) {
        for (auto elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // Add similar examples for dense-sparse and sparse-sparse if needed
    return 0;
}

