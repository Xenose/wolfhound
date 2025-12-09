#!/bin/sh


TARGET="$(cat "${PRP}/.target" 2> /dev/null)"
set -eu

cd "${PRP}/${TARGET}"

TOOL="$(grep "^CMAKE_GENERATOR:INTERNAL=" ./CMakeCache.txt | cut -d= -f2 | tr '[:upper:]' '[:lower:]')"

if [ "unix makefiles" = "$TOOL" ]; then
	make clean
elif [ "ninja" = "$TOOL" ]; then
	ninja clean
else
	echo "[ compile.sh ] Please select Ninja or Make for building."
fi
