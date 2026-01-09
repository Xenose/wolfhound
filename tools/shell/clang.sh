#!/bin/sh

set -eu

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/clang-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.wolfhound/target"

if [ -n "$ANDROID__BUILD_VERSION_SDK" ]; then
	compiler_path="clang"
	compiler_pp_path="clang++"
else
	compiler_path="$(which clang)"
	compiler_pp_path="$(which clang++)"
fi

if command -v clang > /dev/null && command -v clang++ > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="${compiler_path}" \
		-DCMAKE_CXX_COMPILER="${compiler_pp_path}" \
		-DNO_CXX_COMPILER=FALSE
elif command -v clang > /dev/null; then
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
