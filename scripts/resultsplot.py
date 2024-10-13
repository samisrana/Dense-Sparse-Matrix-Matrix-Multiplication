import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the CSV data
data = pd.read_csv("performance_results.csv")

# Ensure correct data types
data["MatrixSize"] = data["MatrixSize"].astype(int)
data["Sparsity"] = pd.to_numeric(data["Sparsity"], errors='coerce').fillna(0.0)
data["Time(s)"] = data["Time(s)"].astype(float)


def plot_sparsity_performance_from_csv(file_path):
    """
    Reads matrix multiplication performance data from a CSV file and plots it.
    
    Parameters:
    - file_path: Path to the CSV file containing the data.
    """
    # Load data from the CSV
    df = pd.read_csv(file_path)

    # Ensure correct data types
    df["MatrixSize"] = df["MatrixSize"].astype(int)
    df["Sparsity"] = pd.to_numeric(df["Sparsity"], errors='coerce').fillna(0.0)
    df["Time(s)"] = df["Time(s)"].astype(float)

    # Extract unique matrix sizes and sparsity levels
    matrix_sizes = sorted(df["MatrixSize"].unique())
    sparsity_levels = sorted(df["Sparsity"].unique())

    # Initialize a 2D list to store times
    times = [[None] * len(matrix_sizes) for _ in sparsity_levels]

    # Populate the times list with execution times from the DataFrame
    for i, sparsity in enumerate(sparsity_levels):
        for j, size in enumerate(matrix_sizes):
            # Filter the DataFrame for matching size and sparsity
            filtered = df[(df["MatrixSize"] == size) & (df["Sparsity"] == sparsity)]

            if not filtered.empty:
                # Extract the time value if the filtered data is not empty
                times[i][j] = filtered["Time(s)"].values[0]
            else:
                # Handle cases where no matching data is found
                print(f"No data for Matrix Size={size}, Sparsity={sparsity}")

    # Plot the results
    plt.figure(figsize=(8, 6))
    for i, sparsity in enumerate(sparsity_levels):
        valid_times = [t for t in times[i] if t is not None]  # Filter out None values
        valid_sizes = [matrix_sizes[k] for k, t in enumerate(times[i]) if t is not None]

        plt.plot(valid_sizes, valid_times, marker='o', linestyle='--', label=f'{sparsity}% Sparsity')

    # Add labels, title, legend, and grid
    plt.xlabel('Matrix Size (N x N)')
    plt.ylabel('Time (seconds)')
    plt.title('Matrix Multiplication Performance with Different Sizes and Sparsity Levels')
    plt.legend(title='Sparsity')
    plt.grid(True)

    # Display the plot
    plt.show()

def analyze_performance(file_path):
    # Load data
    df = pd.read_csv(file_path)

    # Clean sparsity values (replace NaN with 0 for dense-dense matrices)
    df["Sparsity"] = df["Sparsity"].fillna(0)

    # Ensure correct data types
    df["MatrixSize"] = df["MatrixSize"].astype(int)
    df["Sparsity"] = df["Sparsity"].astype(float)

    # Plot settings
    sns.set(style="whitegrid")
    optimizations = ["Native", "Multi-threading", "SIMD", "Cache", "All"]

    # Function to plot matrix type vs time for a specific size and sparsity
    def plot_performance(matrix_size, sparsity, matrix_type):
        data = df[
            (df["MatrixSize"] == matrix_size) &
            (df["Sparsity"] == sparsity) &
            (df["MatrixType"] == matrix_type)
        ]

        if data.empty:
            print(f"No data found for {matrix_type} with size {matrix_size} and sparsity {sparsity}%")
            return

        plt.figure(figsize=(10, 6))
        sns.barplot(data=data, x="Optimization", y="Time(s)", order=optimizations)
        plt.title(f"{matrix_type.capitalize()} - Size: {matrix_size}, Sparsity: {sparsity}%")
        plt.show()

    # Plot comparisons for different configurations
    def compare_performance(matrix_size, sparsity):
        matrix_types = df["MatrixType"].unique()
        for matrix_type in matrix_types:
            plot_performance(matrix_size, sparsity, matrix_type)

    # Generate plots for required scenarios
    compare_performance(1000, 1.0)      # Matrix size 1,000 x 1,000, Sparsity 1%
    compare_performance(10000, 0.1)     # Matrix size 10,000 x 10,000, Sparsity 0.1%

    # Summary statistics
    summary = df.groupby(["MatrixType", "Optimization"])["Time(s)"].mean().reset_index()
    print("\nAverage Time by Matrix Type and Optimization:")
    print(summary)

    # Compare all optimizations across matrix types
    plt.figure(figsize=(12, 6))
    sns.barplot(data=df, x="Optimization", y="Time(s)", hue="MatrixType", order=optimizations)
    plt.title("Performance Comparison Across All Matrix Types and Optimizations")
    plt.show()

def plot_execution_time_line(matrix_type):
    """
    Line plot showing execution time vs matrix size for different optimizations.
    """
    subset = data[data["MatrixType"] == matrix_type]
    
    # Check if the subset has any data
    if subset.empty:
        print(f"No data available for matrix type: {matrix_type}")
        return

    plt.figure(figsize=(12, 6))
    sns.lineplot(
        x="MatrixSize", 
        y="Time(s)", 
        hue="Optimization", 
        style="Optimization", 
        markers=True, 
        data=subset
    )

    # Use log scale if the time range is large
    if subset["Time(s)"].max() / subset["Time(s)"].min() > 10:
        plt.yscale('log')

    plt.title(f"Matrix Multiplication Optimizations: {matrix_type}")
    plt.xlabel("Matrix Size")
    plt.ylabel("Time (seconds)")
    plt.grid(True, linestyle="--", linewidth=0.7)
    plt.legend(title="Optimization", loc="upper left", bbox_to_anchor=(1, 1))
    plt.show()

def plot_bar_optimizations(matrix_size, sparsity=None):
    """
    Bar plot showing the performance for different optimizations.
    """
    if sparsity is not None:
        subset = data[(data["MatrixSize"] == matrix_size) & (data["Sparsity"] == sparsity)]
        title_suffix = f"Sparsity={sparsity}"
    else:
        subset = data[(data["MatrixSize"] == matrix_size) & (data["MatrixType"] == "dense-dense")]
        title_suffix = "Dense-Dense Only"

    # Check if the subset has any data
    if subset.empty:
        print(f"No data available for Matrix Size={matrix_size}, Sparsity={sparsity}")
        return

    plt.figure(figsize=(12, 6))
    sns.barplot(
        x="Optimization", 
        y="Time(s)", 
        hue="MatrixType", 
        data=subset
    )

    plt.title(f"Optimization Comparison (Size={matrix_size}, {title_suffix})")
    plt.ylabel("Time (seconds)")
    plt.xticks(rotation=45)
    plt.grid(True, linestyle="--", linewidth=0.5)
    plt.legend(loc="best")
    plt.show()

def plot_cache_misses_vs_time(matrix_type):
    """
    Scatter plot of cache misses vs. execution time.
    """
    subset = data[data["MatrixType"] == matrix_type]

    # Check if the subset has any data
    if subset.empty:
        print(f"No data available for matrix type: {matrix_type}")
        return

    plt.figure(figsize=(10, 6))
    sns.scatterplot(
        x="CacheMisses", 
        y="Time(s)", 
        hue="Optimization", 
        size="MatrixSize", 
        sizes=(50, 200), 
        data=subset,
        legend="full"
    )

    # Use log scale if needed
    if subset["CacheMisses"].max() / subset["CacheMisses"].min() > 10:
        plt.xscale('log')
        plt.yscale('log')

    plt.title(f"Cache Misses vs Time: {matrix_type}")
    plt.xlabel("Cache Misses (log scale)")
    plt.ylabel("Time (seconds, log scale)")
    plt.grid(True, linestyle="--", linewidth=0.7)
    plt.legend(title="Optimization", loc="best", bbox_to_anchor=(1, 1))
    plt.show()

# Example usage of the plots
plot_sparsity_performance_from_csv("performance_results.csv")
analyze_performance('performance_results.csv')
plot_execution_time_line("dense-dense")
plot_bar_optimizations(1000, 0.01)
plot_bar_optimizations(1000)
plot_cache_misses_vs_time("sparse-sparse")
