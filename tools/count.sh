#!/bin/bash

set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
ENGINE_DIR="$(dirname "${SCRIPT_DIR}")"

cd "${ENGINE_DIR}"

clear
cloc --exclude-dir="build" --force-lang="C",h --force-lang="C++",hpp --fmt=2 .
