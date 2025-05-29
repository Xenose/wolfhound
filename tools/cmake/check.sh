#!/bin/sh

MAYBE="\033[33mMAYBE\033[0m"
YES="\033[32mYES\033[0m"
NO="\033[31mNO\033[0m"

check() {
	NAME="${1}"
	OUT="\033[31mFALSE\033[0m"
	OPT="$NO"

	if command -v "$1" > /dev/null; then
		OUT="\033[32mTRUE \033[0m"
	fi
	
	if [ "" != "$2" ]; then
		OPT="$2"
	fi

	printf "| %-12s | %-16b | %-18b | %-24s |\n" "${NAME}" "${OUT}" "${OPT}" "$3" 
}

check_lib() {
	NAME="${1}"
	OUT="\033[31mFALSE\033[0m"
	OPT="\033[31mNO\033[0m"

	if [ "" != "$(ldconfig -p | grep "$1")" ]; then
		OUT="\033[32mTRUE \033[0m"
	fi

	if [ "" != "$2" ]; then
		OPT="$2"
	fi
	
	printf "| %-12s | %-16b | %-18b | %-24s |\n" "${NAME}" "${OUT}" "${OPT}" "$3"
}

clear

printf "| Program Name | Found   | Optional  | Alternative              |\n"
printf "| ------------ | ------- | --------- | ------------------------ |\n"

check gcc		"$MAYBE" "clang"
check clang		"$MAYBE" "gcc"
check make		"$MAYBE" "ninja"
check ninja		"$MAYBE" "make"
check cmake
check git
check python	"$YES"
check python3	"$YES"
check gfortran	"$YES"
check cloc		"$YES"


printf "\n| Library Name | Found   | Optional  | Alternative              |\n"
printf "| ------------ | ------- | --------- | ------------------------ |\n"

check_lib SDL3		"$MAYBE" "glfw"
check_lib glew		"$MAYBE" "vulkan, SDL3"
check_lib vulkan	"$MAYBE" "glew, SDL3"
check_lib glfw		"$MAYBE" "SDL3"
check_lib lua
check_lib unwind	"$YES"

printf "\n"
