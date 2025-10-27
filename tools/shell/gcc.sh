#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/gcc++
