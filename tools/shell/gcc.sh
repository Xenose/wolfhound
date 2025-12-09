#!/bin/sh

set -e
TARGET="build/gcc-linux"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"
cd "${PRP}/${TARGET}"

if command -v gcc > /dev/null && command -v g++ > /dev/null; then
	cmake "${PRP}" -DCMAKE_C_COMPILER="$(which gcc)" -DCMAKE_CXX_COMPILER="$(which g++)" -DNO_CXX_COMPILER=FALSE
elif command -v gcc > /dev/null && command -v gcc++ > /dev/null; then
	cmake "${PRP}" -DCMAKE_C_COMPILER="$(which gcc)" -DCMAKE_CXX_COMPILER="$(which gcc++)" -DNO_CXX_COMPILER=FALSE
elif command -v gcc > /dev/null; then
	echo "[WARNING] g++ is not installed, running in C only mode" 
	cmake "${PRP}" -DCMAKE_C_COMPILER="$(which gcc)" -DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] gcc is not installed, exiting..."
	exit 1
fi
