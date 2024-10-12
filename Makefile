# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -mavx -mavx2 -mfma -pthread

# Directories for header files and source files
INCLUDE_DIRS = -Iinclude
SRC_DIR = src/matrix
OPTIMIZATION_DIR = src/optimizations

# Object files
OBJ = main.o multiplication.o matrix_gen.o simd_optimization.o cache_optimization.o

# Executable name
OUTPUT = matrix_mult

# Rule to build the final executable
$(OUTPUT): $(OBJ)
	$(CXX) -o $(OUTPUT) $(OBJ) $(CXXFLAGS)

# Rule to compile main.cpp
main.o: main.cpp include/matrix/multiplication.h include/matrix/matrix_gen.h
	$(CXX) -c main.cpp $(CXXFLAGS) $(INCLUDE_DIRS)

# Rule to compile multiplication.cpp
multiplication.o: $(SRC_DIR)/multiplication.cpp include/matrix/multiplication.h
	$(CXX) -c $(SRC_DIR)/multiplication.cpp -o multiplication.o $(CXXFLAGS) $(INCLUDE_DIRS)

# Rule to compile matrix_generator.cpp
matrix_gen.o: $(SRC_DIR)/matrix_gen.cpp include/matrix/matrix_gen.h
	$(CXX) -c $(SRC_DIR)/matrix_gen.cpp -o matrix_gen.o $(CXXFLAGS) $(INCLUDE_DIRS)

# Rule to compile simd_optimization.cpp
simd_optimization.o: $(OPTIMIZATION_DIR)/simd_optimization.cpp include/optimizations/simd_optimization.h
	$(CXX) -c $(OPTIMIZATION_DIR)/simd_optimization.cpp -o simd_optimization.o $(CXXFLAGS) $(INCLUDE_DIRS)

# Rule to compile cache_optimization.cpp
cache_optimization.o: $(OPTIMIZATION_DIR)/cache_optimization.cpp include/optimizations/cache_optimization.h
	$(CXX) -c $(OPTIMIZATION_DIR)/cache_optimization.cpp -o cache_optimization.o $(CXXFLAGS) $(INCLUDE_DIRS)

# Clean up build files
clean:
	rm -f *.o $(OUTPUT)

# Phony targets
.PHONY: clean
