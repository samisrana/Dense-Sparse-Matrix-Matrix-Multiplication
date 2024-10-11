#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <vector> //vector data structure for dynamically resizable arrays, used to represent matrices

// Function declaration for matrix multiplication
// Takes 2 inputs, A and B, & multiplies them O(n^3) through a iterative approach of traditionally multipling matrices manually
std::vector<std::vector<int>> matrix_multiplication(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B);

#endif // MULTIPLICATION_H
