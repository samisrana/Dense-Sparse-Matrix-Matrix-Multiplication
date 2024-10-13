#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "matrix/multiplication.h"
#include "matrix/matrix_gen.h"

// Helper to ask for matrix dimensions
void get_matrix_size(int& rows, int& cols) {
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;
}

// Helper to ask for sparsity percentage
double get_sparsity() {
    double sparsity;
    std::cout << "Enter the sparsity percentage (e.g., 10 for 10%): ";
    std::cin >> sparsity;
    return sparsity / 100.0;  // Convert to decimal
}

// Matrix generation wrapper
std::vector<std::vector<int>> generate_matrix(bool is_sparse, int rows, int cols, double sparsity = 0) {
    if (is_sparse) {
        return generate_sparse_matrix(rows, cols, sparsity);
    } else {
        return generate_dense_matrix(rows, cols);
    }
}

// Helper to print matrix
void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}

// Parse the print flag from command-line arguments
bool parse_print_flag(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <print_flag: 1 or 0>\n";
        exit(EXIT_FAILURE);
    }

    int flag = std::atoi(argv[1]);
    if (flag != 0 && flag != 1) {
        std::cerr << "Invalid value for print_flag. Use 1 to print, 0 to skip.\n";
        exit(EXIT_FAILURE);
    }
    return flag == 1;
}

int main(int argc, char* argv[]) {
    // Parse print flag from command-line arguments
    bool print_result = parse_print_flag(argc, argv);

    std::string multiplication_type;
    int rowsA, colsA, rowsB, colsB;
    bool use_sparse_A = false, use_sparse_B = false;

    std::cout << "Select matrix multiplication type (dense-dense, dense-sparse, sparse-sparse): ";
    std::cin >> multiplication_type;

    if (multiplication_type == "dense-dense") {
        use_sparse_A = false;
        use_sparse_B = false;
    } else if (multiplication_type == "dense-sparse") {
        use_sparse_A = false;
        use_sparse_B = true;
    } else if (multiplication_type == "sparse-sparse") {
        use_sparse_A = true;
        use_sparse_B = true;
    } else {
        std::cerr << "Invalid multiplication type. Exiting...\n";
        return EXIT_FAILURE;
    }

    // Ask for matrix sizes
    std::cout << "Enter the dimensions for Matrix A:\n";
    get_matrix_size(rowsA, colsA);

    std::cout << "Enter the dimensions for Matrix B:\n";
    get_matrix_size(rowsB, colsB);

    // Ensure multiplication is valid
    if (colsA != rowsB) {
        std::cerr << "Invalid matrix dimensions: Columns of A must match rows of B.\n";
        return EXIT_FAILURE;
    }

    // Ask for sparsity if necessary
    double sparsityA = 0, sparsityB = 0;
    if (use_sparse_A) {
        std::cout << "Enter sparsity percentage for Matrix A:\n";
        sparsityA = get_sparsity();
    }
    if (use_sparse_B) {
        std::cout << "Enter sparsity percentage for Matrix B:\n";
        sparsityB = get_sparsity();
    }

    // Generate matrices
    std::cout << "Generating matrices...\n";
    auto A = generate_matrix(use_sparse_A, rowsA, colsA, sparsityA);
    auto B = generate_matrix(use_sparse_B, rowsB, colsB, sparsityB);

    // Ask for number of threads and optimizations
    int num_threads;
    bool use_multithreading, use_simd, use_cache_optimization;

    std::cout << "Enter the number of threads: ";
    std::cin >> num_threads;

    std::cout << "Enable multi-threading? (1 for yes, 0 for no): ";
    std::cin >> use_multithreading;

    std::cout << "Enable SIMD optimization? (1 for yes, 0 for no): ";
    std::cin >> use_simd;

    std::cout << "Enable cache optimization? (1 for yes, 0 for no): ";
    std::cin >> use_cache_optimization;

    // Perform matrix multiplication
    std::cout << "Performing matrix multiplication...\n";
    auto result = matrix_multiplication(A, B, use_multithreading, use_simd, use_cache_optimization, num_threads);

    // Print the result if the flag is enabled
    if (print_result) {
        std::cout << "Resulting matrix:\n";
        print_matrix(result);
    } else {
    }

    return 0;
}
