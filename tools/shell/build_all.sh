#!/bin/sh

set -eu

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGETS=""

if command -v clang > /dev/null; then
	TARGETS="${TARGETS} clang-${SYS}"
fi

if command -v gcc > /dev/null; then
	TARGETS="${TARGETS} gcc-${SYS}"
fi

if command -v tcc > /dev/null; then
	TARGETS="${TARGETS} tcc-${SYS}"
fi

if command -v ixc > /dev/null; then
	TARGETS="${TARGETS} ixc-${SYS}"
fi

if command -v zig > /dev/null; then
	TARGETS="${TARGETS} zig-${SYS}"
fi

if command -v cmake > /dev/null; then
	for target in ${TARGETS}; do
		echo "--> Trarget ${target}"

		mkdir -pv "${PRP}/build/${target}"

		set +e
		cmake --build "${PRP}/build/${target}" 
		set -e
	done
else
	echo "CMake not installed exiting..."
	exit 1
fi

mkdir -pv "${PRP}/build/bin/"

for f in $(find "${PRP}/build/" ! -path '*/CMakeFiles/*' -type f -executable -print | tr '\n' ' '); do
	compiler="$(echo "$f" | cut -b "$((${#PRP} + 2))"- | tr '/' ' ' | awk '{ print $2 }')"
	file="$(basename "${f}")"
	
	echo "${file}-${compiler}"
	ln -sf "$f" "${PRP}/build/bin/${file}-${compiler}"
done
