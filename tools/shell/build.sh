#!/bin/sh

set -e

mkdir -pv "${PRP}/build"

if command -v cmake > /dev/null; then
	cmake --build "${PRP}/build" 
else
	echo "CMake not installed exiting..."
	exit 1
fi
