#!/bin/bash

# We want the path to remain in the activated
# folder only
# shellcheck disable=SC2139

WP=$(dirname "$(readlink -f "$0")")
WP=$(dirname "$WP")
WP=$(dirname "$WP")

echo "Setting active directory to [ $WP ]"

# Fun
alias wh-stats="PRP='${WP}' ${WP}/tools/cmake/stats.sh"

# Helpers
alias wh-check="PRP='${WP}' ${WP}/tools/cmake/check.sh"

# code
alias wh-build="PRP='${WP}' ${WP}/tools/cmake/compile.sh"
alias wh-clean="PRP='${WP}' ${WP}/tools/cmake/clean.sh"

# compilers
alias wh-clang="PRP='${WP}' ${WP}/tools/cmake/clang.sh"
alias wh-mingw="PRP='${WP}' ${WP}/tools/cmake/mingw.sh"

# build systems
alias wh-ninja="PRP='${WP}' ${WP}/tools/cmake/ninja.sh"
alias wh-make="PRP='${WP}' ${WP}/tools/cmake/make.sh"
