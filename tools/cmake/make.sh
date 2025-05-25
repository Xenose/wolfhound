#!/bin/sh

set -e

cd "${PRP}/build"
rm CMakeCache.txt

cmake -G "Unix Makefiles" ..
