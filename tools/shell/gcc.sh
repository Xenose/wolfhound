#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc

if command -v g++ > /dev/null; then
	cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/g++
else
	cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/gcc++
fi
