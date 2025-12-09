#!/bin/sh


TARGET="$(cat "${PRP}/.target" 2> /dev/null)"
set -e

if [ -z "${TARGET}" ]; then
	echo "ERROR :: please select a compiler by running wh-[compiler-name]"
	exit 1
fi

cd "${PRP}/${TARGET}"
rm "CMakeCache.txt" || True
cmake -G "Unix Makefiles" "${PRP}"
