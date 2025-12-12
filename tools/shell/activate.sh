#!/bin/sh

# We want the path to remain in the activated
# folder only
# shellcheck disable=SC2139

if [ -f /.dockerenv ]; then
	echo "Running inside Docker, using current path instead!"
	WP=$(pwd)
elif [ ! -z "$ANDROID__BUILD_VERSION_SDK" ]; then
	echo "Running inside Android, using current path instead!"
	WP=$(pwd)
else
	echo "Not running inside Docker"
	WP=$(cd "$(dirname "$0")" && pwd)
	WP=$(dirname "$WP")
	WP=$(dirname "$WP")
fi

#. "${WP}${TP}docker.sh"
__wh_docker() {
	docker build -t "test_image_wolfhound" -f "${PRP}/tools/docker/${1}.dockerfile" "${PRP}"
	docker run --rm -it -v "$PWD":/wolfhound "test_image_wolfhound"
	docker rmi "test_image_wolfhound"
}

# The tools foolder
TP="/tools/shell/"
echo "Setting active directory to [ $WP ]"

# Fun
alias wh-count="PRP='${WP}' ${WP}${TP}stats.sh"

# Tests / Reviews
alias wh-ai-review="PRP='${WP}' ${WP}${TP}ai_review.sh"
alias wh-coverage="PRP='${WP}' ${WP}${TP}coverage.sh"

# Helpers
alias wh-refresh=". ${WP}${TP}activate.sh"
alias wh-bootstrap="PRP='${WP}' ${WP}${TP}bootstrap.sh"
alias wh-check="PRP='${WP}' ${WP}${TP}check.sh"
alias wh-docker="PRP='${WP}' __wh_docker"
alias wh-sync="PRP='${WP}' ${WP}${TP}sync.sh"

# code
alias wh-build="PRP='${WP}' ${WP}${TP}build.sh"
alias wh-build-all="PRP='${WP}' ${WP}${TP}build_all.sh"
alias wh-clean="PRP='${WP}' ${WP}${TP}clean.sh"

# compilers
alias wh-gcc="PRP='${WP}' ${WP}${TP}gcc.sh"
alias wh-clang="PRP='${WP}' ${WP}${TP}clang.sh"
alias wh-mingw="PRP='${WP}' ${WP}${TP}mingw.sh"
alias wh-tcc="PRP='${WP}' ${WP}${TP}tcc.sh"

# build systems
alias wh-ninja="PRP='${WP}' ${WP}${TP}ninja.sh"
alias wh-make="PRP='${WP}' ${WP}${TP}make.sh"
