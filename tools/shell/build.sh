#!/bin/sh

set -e

SYS="$("${PRP}/${TP}"/detect_sys.sh)"
TARGET="$(cat "${PRP}/.wolfhound/target")"
mkdir -pv "${PRP}/${TARGET}"

if ! echo "${TARGET}" | grep -e "${SYS}"; then
	echo "Target [ ${TARGET} :: ${SYS} ] is incorrect run [ wh-clang, wh-tcc, wh-gcc, wh-mingw, wh-msvc ] to fix this"
	exit 1
fi

if command -v cmake > /dev/null; then
	printf "Building target [ %s ]\n\n" "$(basename "${TARGET}")"
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
