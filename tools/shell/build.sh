#!/bin/sh

set -e

TARGET="$(cat "${PRP}/.target")"
mkdir -pv "${PRP}/${TARGET}"

if command -v cmake > /dev/null; then
	cmake --build "${PRP}/${TARGET}" 
else
	echo "CMake not installed exiting..."
	exit 1
fi

mkdir -pv "${PRP}/build/bin/"

for f in $(find "${PRP}/${TARGET}" ! -path '*/CMakeFiles/*' -type f -executable -print | tr '\n' ' '); do
	compiler="$(echo "$f" | cut -b "$((${#PRP} + 2))"- | tr '/' ' ' | awk '{ print $2 }')"
	file="$(basename "${f}")"
	
	echo "${file}-${compiler}"
	ln -sf "$f" "${PRP}/build/bin/${file}-${compiler}"
done
