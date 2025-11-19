#!/bin/sh

set -e

cd "${PRP}"

"${PRP}/tools/shell/clean.sh"

cd "${PRP}/build"
cmake .. -DGENERATE_REPORT=on
cd "${PRP}"

"${PRP}/tools/shell/build.sh" 
"${PRP}/build/tests/cpp/gtests/gtests"

mkdir -pv "${PRP}/reports"
rm -rf "${PRP}/reports/coverage.info" reports/coverage

lcov --ignore-errors source --ignore-errors inconsistent --capture --directory "${PRP}/build" --output-file "${PRP}/reports/coverage.info"
lcov --ignore-errors source --ignore-errors inconsistent --remove "${PRP}/reports/coverage.info" "*tests/*" --output-file "${PRP}/reports/coverage.info"  # optional filter
genhtml "${PRP}/reports/coverage.info" --output-directory "${PRP}/reports/coverage"

find build -name "${PRP}/*.gcda" -o -name "${PRP}/*.gcno" -delete
xdg-open "${PRP}/reports/coverage/index.html" 2>/dev/null || open "${PRP}/reports/coverage/index.html" 2>/dev/null || true
