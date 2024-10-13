#!/bin/bash

# Output CSV file to store the results
RESULTS_FILE="performance_results.csv"

# Get the number of available CPU cores
NUM_CORES=$(nproc)

# Ensure the results file exists and has the correct header
echo "MatrixType,MatrixSize,Sparsity,Optimization,NumThreads,Time(s),Instructions,Cycles,CacheMisses" > $RESULTS_FILE

# Function to run the matrix multiplication with a specific configuration using perf
run_experiment() {
    matrix_type=$1
    size=$2
    sparsity=$3
    opt_type=$4  # Optimization type (e.g., native, multi-threading, etc.)
    num_threads=$5
    print_flag=0  # Disable printing to avoid unnecessary output

    # Run perf to measure execution time and hardware metrics
    perf stat -e instructions,cycles,cache-misses -o perf_output.txt \
    ./matrix_mult $print_flag <<EOF
$matrix_type
$size
$size
$size
$size
$sparsity
$sparsity
$num_threads  # Number of threads
$opt_type  # Enable multi-threading?
$opt_type  # Enable SIMD optimization?
$opt_type  # Enable cache optimization?
EOF

    # Extract metrics from perf output
    time=$(grep "seconds time elapsed" perf_output.txt | awk '{print $1}')
    instructions=$(grep "instructions" perf_output.txt | awk '{print $1}' | sed 's/,//g')
    cycles=$(grep "cycles" perf_output.txt | awk '{print $1}' | sed 's/,//g')
    cache_misses=$(grep "cache-misses" perf_output.txt | awk '{print $1}' | sed 's/,//g')

    # Save the results to the CSV file
    echo "$matrix_type,$size,$sparsity,$opt_type,$num_threads,$time,$instructions,$cycles,$cache_misses" >> $RESULTS_FILE

    # Clean up the perf output file
    rm perf_output.txt
}

# Array of matrix types
MATRIX_TYPES=("dense-dense" "dense-sparse" "sparse-sparse")

# Array of matrix sizes
MATRIX_SIZES=(10 100 1000 5000 10000)

# Array of sparsity levels (converted to decimal)
SPARSITY_LEVELS=(0.01 0.001)

# Optimization configurations:
# "native" (no optimizations), "mt" (multi-threading), "simd", "cache", "all"
OPTIMIZATIONS=("native" "mt" "simd" "cache" "all")

#Compile code
make -j$(nproc)

# Run experiments for all combinations
for matrix_type in "${MATRIX_TYPES[@]}"; do
    for size in "${MATRIX_SIZES[@]}"; do
        for sparsity in "${SPARSITY_LEVELS[@]}"; do
            for opt in "${OPTIMIZATIONS[@]}"; do
                if [[ "$opt" == "mt" || "$opt" == "all" ]]; then
                    # Use $(nproc) cores for multi-threading experiments
                    run_experiment "$matrix_type" "$size" "$sparsity" 1 "$NUM_CORES"
                else
                    # Use single-thread for native or non-multi-threaded optimizations
                    run_experiment "$matrix_type" "$size" "$sparsity" 0 1
                fi
            done
        done
    done
done

echo "Experiments completed! Results saved to $RESULTS_FILE."
python3 resultsplot.py
