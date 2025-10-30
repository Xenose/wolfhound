#!/bin/sh

set -e

SCRIPT_DIR=$(dirname -- "$( readlink -f -- "$0"; )")

if ! command -v cloc > /dev/null; then
	echo "Error [ cloc ] not installed please install it"
	exit 1
fi

python3 "${SCRIPT_DIR}/source/main.py"
