#!/bin/bash

WP=$(dirname "$(readlink -f "$0")")
WP=$(dirname "$WP")
WP=$(dirname "$WP")

# code
alias wh-build="PRP='${WP}' ${WP}/tools/cmake/compile.sh"

# compilers
alias wh-clang="PRP='${WP}' ${WP}/tools/cmake/clang.sh"
alias wh-mingw="PRP='${WP}' ${WP}/tools/cmake/mingw.sh"

# build systems
alias wh-ninja="PRP='${WP}' ${WP}/tools/cmake/ninja.sh"
alias wh-make="PRP='${WP}' ${WP}/tools/cmake/make.sh"
