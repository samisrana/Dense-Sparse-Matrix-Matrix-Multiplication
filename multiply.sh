#!/bin/bash
#set -x

# Run the Makefile to build the project
echo "Building the project..."
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful."

    # Run the generated executable
    echo "Running the program... xD"
    ./matrix_mult 1

    # Check if the program ran successfully
    if [ $? -eq 0 ]; then
        echo "Program ran successfully."
    else
        echo "Error: The program did not run successfully."
    fi
else
    echo "Build failed. Please check the errors."
fi
