#!/bin/bash
outfile=linux_x64/MapBenchmark
mkdir -p linux_x64
g++ -std=c++17 -march=x86-64 -O3 -Wno-format MapBenchmark.cpp -o $outfile && $outfile
