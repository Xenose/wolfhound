#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

cmake .. -DCMAKE_C_COMPILER=/usr/bin/x86_64-w64-mingw32-gcc
