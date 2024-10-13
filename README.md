# Dense and Sparse Matrix Multiplication with Multi-threading, SIMD, and Cache Optimization

## Table of Contents
1. [Introduction](#introduction)
2. [Project Features](#project-features)
3. [Setup Instructions](#setup-instructions)
4. [Dependencies](#dependencies)
5. [How to Run the Experiments](#how-to-run-the-experiments)
6. [Experiments and Results](#experiments-and-results)  
   - [Optimization Impact](#optimization-impact)  
   - [Dense-Dense Matrix Multiplication](#dense-dense-matrix-multiplication)  
   - [Sparse-Sparse Matrix Multiplication](#sparse-sparse-matrix-multiplication)  
   - [Dense-Sparse Matrix Multiplication](#dense-sparse-matrix-multiplication)
7. [Final Analysis and Conclusions](#final-analysis-and-conclusions)
8. [Future Implementations](#future-implementations)

---

## Introduction
This project implements high-performance **dense-dense, dense-sparse, and sparse-sparse matrix multiplication** using C++ with configurable **multi-threading, SIMD optimizations**, and **cache miss minimization techniques**. The software allows you to experiment with **arbitrary matrix sizes** and sparsity levels, providing flexibility to analyze performance for different configurations.

Matrix multiplication is a critical operation in many fields such as **machine learning, computer vision, and scientific computing**. This project provides tools to evaluate how various optimization techniques impact performance under different matrix sizes and sparsities.

---

## Project Features
- **Arbitrary Matrix Sizes:** Supports matrix sizes larger than the cache capacity (e.g., up to **10,000 x 10,000**).
- **Configurable Multi-threading:** Users can specify the **number of threads** to utilize.
- **Configurable SIMD Optimizations:** SIMD-based multiplication can be enabled or disabled.
- **Configurable Cache Optimization:** Cache blocking and access pattern optimizations are tunable.
- **Thread Configuration:** Users can easily modify the **number of threads** to measure performance scalability.

---

## Setup Instructions

### Installation
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/samisrana/Dense-Sparse-Matrix-Matrix-Multiplication.git
   cd Dense-Sparse-Matrix-Matrix-Multiplication

## Dependencies

The following dependencies are required to build, run, and analyze the project:

### Build Dependencies
- **C++ Compiler:** `g++` with AVX/AVX2 support for SIMD operations.
- **CMake:** (Optional) To manage the build process.

### Performance Tools
- **perf:** A Linux performance analysis tool to gather performance metrics such as cache misses, CPU cycles, and thread utilization.

### Python Libraries
For visualization and analysis of results:
- **matplotlib:** `pip install matplotlib`  
- **seaborn:** `pip install seaborn`
- **pandas** `pip install pandas`
### Operating System
- **Linux:** Recommended for multi-threading and performance measurement compatibility with `perf`.

Make sure all dependencies are properly installed before proceeding with the experiments.

