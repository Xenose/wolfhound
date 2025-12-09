#!/bin/sh

set -e

TARGET="build/tcc-linux"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"
cd "${PRP}/${TARGET}"

if command -v tcc > /dev/null; then
	echo "[WARNING] c++ is not supported by TCC, running in C only mode" 
	cmake "${PRP}" \
		-DNO_CXX_COMPILER=TRUE \
		-DCMAKE_C_COMPILER="$(which tcc)"
else
	echo "[FAILURE] TCC is not installed, exiting..."
	exit 1
fi
