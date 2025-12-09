#!/bin/sh

set -eu
TARGET="build/mingw-windows"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"

if command -v x86_64-w64-mingw32-gcc > /dev/null && command -v x86_64-w64-mingw32-g++ > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DLINUX_MINGW_WIN=true \
		-DCMAKE_C_COMPILER="$(which x86_64-w64-mingw32-gcc)" \
		-DCMAKE_CXX_COMPILER="$(which x86_64-w64-mingw32-g++)" \
		-DNO_CXX_COMPILER=FALSE
elif command -v x86_64-w64-mingw32-gcc > /dev/null; then
	echo "[WARNING] x86_64-w64-mingw32-g++ is not installed, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DLINUX_MINGW_WIN=true \
		-DCMAKE_C_COMPILER="$(which x86_64-w64-mingw32-gcc)" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] mingwh is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
