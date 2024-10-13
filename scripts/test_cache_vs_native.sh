#!/bin/bash

# Output CSV file for storing the results
RESULTS_FILE="cache_vs_native_results.csv"

# Ensure the results file exists with the correct header
echo "MatrixSize,Implementation,Time(s)" > $RESULTS_FILE

# Function to run matrix multiplication with a specific implementation
run_test() {
    size=$1  # Matrix size (NxN)
    implementation_label=$2  # "Native" or "Cache-Optimized"
    use_cache=$3  # 1 for cache optimization, 0 for native implementation

    # Disable print output during the matrix multiplication
    print_flag=0

    # Run the matrix multiplication and measure the execution time
    start_time=$(date +%s.%N)  # Start time in seconds
    ./matrix_mult $print_flag <<EOF
dense-dense
$size
$size
$size
$size
0.0
0.0
1  # Single thread
0  # No multi-threading
0  # No SIMD
$use_cache  # Use cache optimization (1 or 0)
EOF
    end_time=$(date +%s.%N)  # End time in seconds

    # Calculate elapsed time
    elapsed_time=$(echo "$end_time - $start_time" | bc -l)

    # Write results to the CSV file
    echo "$size,$implementation_label,$elapsed_time" >> $RESULTS_FILE
}

# Array of matrix sizes to test
MATRIX_SIZES=(10 100 500 1000 2000)

# Run tests for each matrix size using native and cache-optimized implementations
for size in "${MATRIX_SIZES[@]}"; do
    echo "Testing Native Implementation for Size $size..."
    run_test $size "Native" 0  # Run native implementation

    echo "Testing Cache-Optimized Implementation for Size $size..."
    run_test $size "Cache-Optimized" 1  # Run cache-optimized implementation
done

echo "Tests completed. Results saved to $RESULTS_FILE."
