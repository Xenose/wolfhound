#!/bin/sh

set -e

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/tcc-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.target"

if command -v tcc > /dev/null; then
	echo "[WARNING] c++ is not supported by TCC, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DNO_CXX_COMPILER=TRUE \
		-DCMAKE_C_COMPILER="$(which tcc)"
else
	echo "[FAILURE] TCC is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
