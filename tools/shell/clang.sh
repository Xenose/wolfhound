#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

if command -v clang > /dev/null && command -v clang++ > /dev/null; then
	cmake .. -DCMAKE_C_COMPILER="$(which clang)" -DCMAKE_CXX_COMPILER="$(which clang++)" -DNO_CXX_COMPILER=FALSE
elif command -v clang > /dev/null; then
	echo "[WARNING] clang++ is not installed, running in C only mode" 
	cmake .. -DCMAKE_C_COMPILER="$(which clang)" -DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] clang is not installed, exiting..."
	exit 1
fi
