#!/bin/sh

set -e

SCRIPT_DIR=$(dirname -- "$( readlink -f -- "$0"; )")

python3 "${SCRIPT_DIR}/source/main.py"
