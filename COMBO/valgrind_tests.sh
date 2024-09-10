#!/bin/bash

PROGRAM_PATH="./cub3d"

INVALID_MAPS_DIR="./maps/invalid"
VALID_MAPS_DIR="./maps/valid"

REPORT_FILE="valgrind_report.txt"

# ANSI color codes
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # No Color

# Clear the report file if it exists
> "$REPORT_FILE"

run_valgrind_test() {
    local map_file=$1
    local map_type=$2

    # Echo the map being tested to both console and file
    echo "Testing $map_type map: $(basename "$map_file")" | tee -a "$REPORT_FILE"
    
    # Run Valgrind and capture its output
    valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 "$PROGRAM_PATH" "$map_file" 2>&1)
    valgrind_exit_code=$?

    # Check for "ERROR SUMMARY: 0 errors from 0 contexts"
    if [[ $valgrind_output == *"ERROR SUMMARY: 0 errors from 0 contexts"* ]]; then
        valgrind_exit_code=0
    fi
    
    if [ $valgrind_exit_code -eq 0 ]; then
        # Print to console with color, but append to file without color
        echo -e "${GREEN}[Valgrind OK]${NC}" | tee -a >(sed 's/\x1b\[[0-9;]*m//g' >> "$REPORT_FILE")
    else
        # Print to console with color, but append to file without color
        echo -e "${RED}Valgrind found issues:${NC}" | tee -a >(sed 's/\x1b\[[0-9;]*m//g' >> "$REPORT_FILE")
        echo "$valgrind_output" >> "$REPORT_FILE"
    fi
    
    # Append a separator to both console and file
    echo "--------------------------------" | tee -a "$REPORT_FILE"
}

# Test invalid maps
if [ -d "$INVALID_MAPS_DIR" ]; then
    for map_file in "$INVALID_MAPS_DIR"/*; do
        if [ -f "$map_file" ]; then
            run_valgrind_test "$map_file" "invalid"
        else
            echo "No files found in $INVALID_MAPS_DIR" | tee -a "$REPORT_FILE"
            exit 1
        fi
    done
else
    echo "Invalid maps directory not found!" | tee -a "$REPORT_FILE"
    exit 1
fi

# Test valid maps
if [ -d "$VALID_MAPS_DIR" ]; then
    for map_file in "$VALID_MAPS_DIR"/*; do
        if [ -f "$map_file" ]; then
            run_valgrind_test "$map_file" "valid"
        else
            echo "No files found in $VALID_MAPS_DIR" | tee -a "$REPORT_FILE"
            exit 1
        fi
    done
else
    echo "Valid maps directory not found!" | tee -a "$REPORT_FILE"
    exit 1
fi
