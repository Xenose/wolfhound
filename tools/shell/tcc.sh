#!/bin/sh

set -e

mkdir -pv "${PRP}/build"
cd "${PRP}/build"

if command -v tcc > /dev/null; then
	echo "[WARNING] c++ is not supported by TCC, running in C only mode" 
	cmake .. \
		-DNO_CXX_COMPILER=TRUE \
		-DCMAKE_C_COMPILER="$(which tcc)"
else
	echo "[FAILURE] clang is not installed, exiting..."
	exit 1
fi
