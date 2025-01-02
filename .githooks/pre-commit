#!/bin/bash
set -e  # Exit if any command fails

# Directories to search for C++ files
SRC_DIRS=("include" "tests")

# Find all C++ files (.cpp, .h, .hpp) to check
FILES=$(find "${SRC_DIRS[@]}" -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" \))

# Run clang-format on each file
for FILE in $FILES; do
    clang-format -i "$FILE"
    echo "Formatted file: $FILE"
done

echo "All files have been formatted!"