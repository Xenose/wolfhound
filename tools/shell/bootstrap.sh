#!/bin/sh

set -e

cd "${PRP}/tools/shell/packages"

PKGS=""
PKGS_FILE=""
COMMAND=""

if command -v pacman > /dev/null; then
	echo "Assuming arch!"
	COMMAND="pacman --needed -S"
	PKGS_FILE="arch.pkgs"
else
	echo "Not Disro found!"
	exit 1
fi

if [ ! -f "${PKGS_FILE}" ]; then
	echo "No package file found!"
	exit 1
fi

while read -r p; do
	PKGS="$PKGS${PKGS:+ }${p}"
done < "${PKGS_FILE}"

if [ -z "${PKGS}" ]; then
	echo "No packages given!"
	exit 1
fi

if [ -n "$PKGS" ]; then
	su -c "${COMMAND} ${PKGS}"
else
	echo "arch.pkgs is empty, nothing to install."
fi
