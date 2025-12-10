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

mkdir -pv "${PRP}/build/bin/"

for f in $(find "${PRP}/build/" ! -path '*/CMakeFiles/*' -type f -executable -print | tr '\n' ' '); do
	compiler="$(echo "$f" | cut -b "$((${#PRP} + 2))"- | tr '/' ' ' | awk '{ print $2 }')"
	file="$(basename "${f}")"
	
	echo "${file}-${compiler}"
	ln -sf "$f" "${PRP}/build/bin/${file}-${compiler}"
done
