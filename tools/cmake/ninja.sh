#!/bin/sh


set -e
cd "${PRP}/build"

set +e
rm CMakeCache.txt
set -e

cmake -G "Ninja" ..
