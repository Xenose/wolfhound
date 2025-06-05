#!/bin/bash

set -e

cd "${PRP}"

clear
cloc --exclude-dir="build" --force-lang="C",h --force-lang="C++",hpp --fmt=2 .
