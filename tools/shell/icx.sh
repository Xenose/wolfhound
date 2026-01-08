#!/bin/sh

set -e
SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="build/icx-${SYS}"

mkdir -pv "${PRP}/${TARGET}"
echo "/${TARGET}" > "${PRP}/.wolfhound/target"
#cd "${PRP}/${TARGET}"

if command -v icx > /dev/null && command -v icpx > /dev/null; then
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which icx)" \
		-DCMAKE_CXX_COMPILER="$(which icpx)" \
		-DNO_CXX_COMPILER=FALSE
elif command -v icx > /dev/null; then
	echo "[WARNING] icpx is not installed, running in C only mode" 
	cmake \
		-S "${PRP}" \
		-B "${PRP}/${TARGET}" \
		-DCMAKE_C_COMPILER="$(which icx)" \
		-DNO_CXX_COMPILER=TRUE
else
	echo "[FAILURE] icx is not installed, exiting..."
	exit 1
fi

cd "${PRP}"
ln -sf "${TARGET}/compile_commands.json" compile_commands.json
