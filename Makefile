# compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -mavx -mavx2 -mfma

# directories for header files and source files
INCLUDE_DIRS = -Iinclude
SRC_DIR = src/matrix

# object files
OBJ = main.o multiplication.o matrix_gen.o

# executable name
OUTPUT = matrix_mult

# rule to build the final executable
$(OUTPUT): $(OBJ)
	$(CXX) -o $(OUTPUT) $(OBJ) $(CXXFLAGS)

# rule to compile main.cpp
main.o: main.cpp include/matrix/multiplication.h include/matrix/matrix_gen.h
	$(CXX) -c main.cpp $(CXXFLAGS) $(INCLUDE_DIRS)

# rule to compile multiplication.cpp
multiplication.o: $(SRC_DIR)/multiplication.cpp include/matrix/multiplication.h
	$(CXX) -c $(SRC_DIR)/multiplication.cpp -o multiplication.o $(CXXFLAGS) $(INCLUDE_DIRS)

# rule to compile matrix_generator.cpp
matrix_gen.o: $(SRC_DIR)/matrix_gen.cpp include/matrix/matrix_gen.h
	$(CXX) -c $(SRC_DIR)/matrix_gen.cpp -o matrix_gen.o $(CXXFLAGS) $(INCLUDE_DIRS)

# clean up build files
clean:
	rm -f *.o $(OUTPUT)

# phony targets
.PHONY: clean
