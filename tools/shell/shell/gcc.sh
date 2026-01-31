#!/bin/sh

ANDROID__BUILD_VERSION_SDK="${ANDROID__BUILD_VERSION_SDK:=}"
set -eu

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/gcc-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.wolfhound/target"

if command -v gcc > /dev/null && command -v g++ > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which gcc)" \
		-DCMAKE_CXX_COMPILER="$(which g++)" \
		-DNO_CXX_COMPILER=FALSE
elif command -v gcc > /dev/null && command -v gcc++ > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which gcc)" \
		-DCMAKE_CXX_COMPILER="$(which gcc++)" \
		-DNO_CXX_COMPILER=FALSE
elif command -v gcc > /dev/null; then
	echo "[WARNING] g++ is not installed, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which gcc)" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] gcc is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
