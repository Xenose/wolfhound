#!/bin/sh

# We want the path to remain in the activated
# folder only
# shellcheck disable=SC2139

if [ -f /.dockerenv ]; then
	echo "Running inside Docker, using current path instead!"
	WP=$(pwd)
else
	echo "Not running inside Docker"
	WP=$(cd "$(dirname "$0")" && pwd)
	WP=$(dirname "$WP")
	WP=$(dirname "$WP")
fi

echo "Setting active directory to [ $WP ]"

# Fun
alias wh-count="PRP='${WP}' ${WP}/tools/shell/stats.sh"

# Helpers
alias wh-refresh=". ${WP}/tools/shell/activate.sh"
alias wh-bootstrap="PRP='${WP}' ${WP}/tools/shell/bootstrap.sh"
alias wh-check="PRP='${WP}' ${WP}/tools/shell/check.sh"
alias wh-docker="PRP='${WP}' ${WP}/tools/shell/docker.sh"

# code
alias wh-build="PRP='${WP}' ${WP}/tools/shell/build.sh"
alias wh-clean="PRP='${WP}' ${WP}/tools/shell/clean.sh"

# compilers
alias wh-clang="PRP='${WP}' ${WP}/tools/shell/clang.sh"
alias wh-mingw="PRP='${WP}' ${WP}/tools/shell/mingw.sh"

# build systems
alias wh-ninja="PRP='${WP}' ${WP}/tools/shell/ninja.sh"
alias wh-make="PRP='${WP}' ${WP}/tools/shell/make.sh"
