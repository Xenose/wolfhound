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
