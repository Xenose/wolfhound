#!/bin/sh

set -e
TARGET="build/clang-linux"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"
cd "${PRP}/${TARGET}"

if command -v clang > /dev/null && command -v clang++ > /dev/null; then
	cmake "${PRP}" -DCMAKE_C_COMPILER="$(which clang)" -DCMAKE_CXX_COMPILER="$(which clang++)" -DNO_CXX_COMPILER=FALSE
elif command -v clang > /dev/null; then
	echo "[WARNING] clang++ is not installed, running in C only mode" 
	cmake "${PRP}" -DCMAKE_C_COMPILER="$(which clang)" -DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] clang is not installed, exiting..."
	exit 1
fi
