#!/bin/bash

# Exit on error
set -e

# Export clang (LSPserver no worky with gcc/++)
export cc=clang
export cxx=clang++

# Configure project with compiler calls for LSPserver
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build project
cmake --build build -j $(nproc)
