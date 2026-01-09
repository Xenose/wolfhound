#!/bin/sh

# We want the path to remain in the activated
# folder only
# shellcheck disable=SC2139

if [ -f /.dockerenv ]; then
	echo "Running inside Docker, using current path instead!"
	WP=$(pwd)
elif [ -n "$ANDROID__BUILD_VERSION_SDK" ]; then
	echo "Running inside Android, using current path instead!"
	WP=$(pwd)
else
	echo "Not running inside Docker"
	WP=$(cd "$(dirname "$0")" && pwd)
	WP=$(dirname "$WP")
	WP=$(dirname "$WP")
fi

if [ -p "tools/shell/activate.sh" ]; then
	echo "Not in the wolfhound directory ABORTING!"
	return 1
fi

# Intel needs its special file
if [ -z "$INTEL_PYTHONHOME" ] && [ -f /opt/intel/oneapi/setvars.sh ]; then
	. /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
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
mkdir -p "${WP}/.wolfhound"

# Fun
alias wh-count="PRP='${WP}' TP='${TP}' ${WP}${TP}stats.sh"

# Tests / Reviews
alias wh-ai-review="PRP='${WP}' TP='${TP}' ${WP}${TP}ai_review.sh"
alias wh-coverage="PRP='${WP}' TP='${TP}' ${WP}${TP}coverage.sh"

# Helpers
alias wh-refresh=". ${WP}${TP}activate.sh"
alias wh-bootstrap="PRP='${WP}' TP='${TP}' ${WP}${TP}bootstrap.sh"
alias wh-check="PRP='${WP}' TP='${TP}' ${WP}${TP}check.sh"
alias wh-docker="PRP='${WP}' TP='${TP}' __wh_docker"
alias wh-sync="PRP='${WP}' TP='${TP}' ${WP}${TP}sync.sh"

# code
alias wh-build="PRP='${WP}' TP='${TP}' ${WP}${TP}build.sh"
alias wh-build-all="PRP='${WP}' TP='${TP}' ${WP}${TP}build_all.sh"
alias wh-clean="PRP='${WP}' TP='${TP}' ${WP}${TP}clean.sh"

# compilers
alias wh-icx="PRP='${WP}' TP='${TP}' ${WP}${TP}icx.sh"
alias wh-gcc="PRP='${WP}' TP='${TP}' ${WP}${TP}gcc.sh"
alias wh-clang="PRP='${WP}' TP='${TP}' ${WP}${TP}clang.sh"
alias wh-mingw="PRP='${WP}' TP='${TP}' ${WP}${TP}mingw.sh"
alias wh-tcc="PRP='${WP}' TP='${TP}' ${WP}${TP}tcc.sh"
alias wh-zig="PRP='${WP}' TP='${TP}' ${WP}${TP}zig.sh"

# build systems
alias wh-ninja="PRP='${WP}' TP='${TP}' ${WP}${TP}ninja.sh"
alias wh-make="PRP='${WP}' TP='${TP}' ${WP}${TP}make.sh"
