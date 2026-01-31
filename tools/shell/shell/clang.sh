#!/bin/sh

ANDROID__BUILD_VERSION_SDK="${ANDROID__BUILD_VERSION_SDK:=}"
set -eu

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/clang-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.wolfhound/target"

# Check the compiler path in normal shells,
# on android we just try the path.
if [ -n "$ANDROID__BUILD_VERSION_SDK" ]; then
	echo "On Android falling back to path!"
	compiler_path="clang"
	compiler_cpp_path="clang++"
else
	compiler_path="$(command -v clang)"
	compiler_cpp_path="$(command -v clang++)"
fi

# Configure the compilers and skip C++ if we don't have a compiler for it.
if [ -n "${compiler_path}" ] && [ -n "${compiler_cpp_path}" ]; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="${compiler_path}" \
		-DCMAKE_CXX_COMPILER="${compiler_cpp_path}" \
		-DNO_CXX_COMPILER=FALSE
elif [ -n "${compiler_path}" ] > /dev/null; then
	echo "[WARNING] clang++ is not installed, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="${compiler_path}" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] clang is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
