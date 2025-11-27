#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

cmake .. \
	-DLINUX_MINGW_WIN=true \
	-DCMAKE_C_COMPILER=/usr/bin/x86_64-w64-mingw32-gcc \
	-DCMAKE_CXX_COMPILER=/usr/bin/x86_64-w64-mingw32-g++
