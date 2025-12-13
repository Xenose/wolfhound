#!/bin/sh

set -eu

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/clang-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"

if command -v clang > /dev/null && command -v clang++ > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which clang)" \
		-DCMAKE_CXX_COMPILER="$(which clang++)" \
		-DNO_CXX_COMPILER=FALSE
elif command -v clang > /dev/null; then
	echo "[WARNING] clang++ is not installed, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which clang)" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] clang is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
