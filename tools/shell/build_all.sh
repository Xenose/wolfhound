#!/bin/sh

set -eu

TARGETS="clang-linux gcc-linux tcc-linux"

if command -v cmake > /dev/null; then
	for target in ${TARGETS}; do
		echo "--> Trarget ${target}"

		mkdir -pv "${PRP}/build/${target}"
		cmake --build "${PRP}/build/${target}" 
	done
else
	echo "CMake not installed exiting..."
	exit 1
fi

