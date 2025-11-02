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

# The tools foolder
TP="/tools/shell/"
echo "Setting active directory to [ $WP ]"

# Fun
alias wh-count="PRP='${WP}' ${WP}${TP}stats.sh"

# Tests / Reviews
alias wh-ai-review="PRP='${WP}' ${WP}${TP}ai_review.sh"
alias wh-covrage="PRP='${WP}' ${WP}${TP}covrage.sh"

# Helpers
alias wh-refresh=". ${WP}${TP}activate.sh"
alias wh-bootstrap="PRP='${WP}' ${WP}${TP}bootstrap.sh"
alias wh-check="PRP='${WP}' ${WP}${TP}check.sh"
alias wh-docker="PRP='${WP}' ${WP}${TP}docker.sh"

# code
alias wh-build="PRP='${WP}' ${WP}${TP}build.sh"
alias wh-clean="PRP='${WP}' ${WP}${TP}clean.sh"

# compilers
alias wh-gcc="PRP='${WP}' ${WP}${TP}gcc.sh"
alias wh-clang="PRP='${WP}' ${WP}${TP}clang.sh"
alias wh-mingw="PRP='${WP}' ${WP}${TP}mingw.sh"

# build systems
alias wh-ninja="PRP='${WP}' ${WP}${TP}ninja.sh"
alias wh-make="PRP='${WP}' ${WP}${TP}make.sh"
