#!/bin/sh

set -e

cd "${PRP}/build"
mkdir -pv "${PRP}/build"

TOOL="$(grep "^CMAKE_GENERATOR:INTERNAL=" ./CMakeCache.txt | cut -d= -f2 | tr '[:upper:]' '[:lower:]')"

if [ "unix makefiles" = "$TOOL" ]; then
	make
elif [ "ninja" = "$TOOL" ]; then
	ninja
else
	echo "[ compile.sh ] Please select Ninja or Make for building."
fi
