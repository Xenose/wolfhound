#!/bin/sh

set -e

cd "${PRP}"

"${PRP}/tools/shell/clean.sh"
"${PRP}/tools/shell/build.sh"
"${PRP}/build/tests/c/compiled_tests"

mkdir -pv reports
rm -rf reports/coverage.info reports/coverage

lcov --capture --directory build --output-file reports/coverage.info
lcov --remove reports/coverage.info "*tests/*" --output-file reports/coverage.info  # optional filter
genhtml reports/coverage.info --output-directory reports/coverage

find build -name "*.gcda" -o -name "*.gcno" -delete
xdg-open reports/coverage/index.html 2>/dev/null || open reports/coverage/index.html 2>/dev/null || true
