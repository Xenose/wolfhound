#!/bin/sh

set -e

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/zig-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.wolfhound/target"

if command -v zig > /dev/null; then
	echo "[WARNING] c++ is not supported by ZIG, running in C only mode" 
	CC="zig cc" \
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] ZIG is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
