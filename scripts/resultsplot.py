import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the CSV data
data = pd.read_csv("performance_results.csv")

# Ensure correct data types
data["MatrixSize"] = data["MatrixSize"].astype(int)
data["Sparsity"] = pd.to_numeric(data["Sparsity"], errors='coerce').fillna(0.0)
data["Time(s)"] = data["Time(s)"].astype(float)

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
plot_execution_time_line("dense-dense")
plot_bar_optimizations(1000, 0.01)
plot_bar_optimizations(1000)
plot_cache_misses_vs_time("sparse-sparse")
