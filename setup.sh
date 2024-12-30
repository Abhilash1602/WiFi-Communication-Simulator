#!/bin/bash

# Make the script itself executable
chmod +x "$0"

# Create directories
mkdir -p build
mkdir -p src
mkdir -p include

# Create placeholder files for organization (optional)
touch build/.gitkeep src/.gitkeep include/.gitkeep

# Move header files to include/ (if present in the current directory)
mv *.h include/ 2>/dev/null

# Move source files to src/ (if present in the current directory)
mv *.cpp src/ 2>/dev/null

echo "File structure setup completed."
echo "Directories: build/, src/, include/"

# Optional: Display usage instructions
echo "Run 'make' to build the project."
echo "Run 'make debug' or 'make optimized' for specific builds."
