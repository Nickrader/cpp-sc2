#!/bin/bash

rm -rf build/_deps/civetweb-*
rm build/CMakeCache.txt

cmake -B build

cmake --build build -j $(nproc)
