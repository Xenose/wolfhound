#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

if command -v gcc > /dev/null && command -v g++ > /dev/null; then
	cmake .. -DCMAKE_C_COMPILER="$(which gcc)" -DCMAKE_CXX_COMPILER="$(which g++)" -DNO_CXX_COMPILER=False
elif command -v gcc > /dev/null && command -v gcc++ > /dev/null; then
	cmake .. -DCMAKE_C_COMPILER="$(which gcc)" -DCMAKE_CXX_COMPILER="$(which gcc++)" -DNO_CXX_COMPILER=False
elif command -v gcc > /dev/null; then
	echo "[WARNING] g++ is not installed, running in C only mode" 
	cmake .. -DCMAKE_C_COMPILER="$(which gcc)" -DNO_CXX_COMPILER=True
else
	echo "[FAILURE] gcc is not installed, exiting..."
	exit 1
fi
