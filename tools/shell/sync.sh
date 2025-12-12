#!/bin/bash

set -eu
SERVER_LIST="${PRP}/.servers"

if ! command -v rsync >/dev/null; then
	echo "This command requires rsync to be installed."
	exit 1
fi

while IFS= read -r line; do
	# skip empty or comment lines
	[ -z "$line" ] && continue
	case "$line" in
		\#*) continue ;;
	esac

	 # split into two fields: destination and port
	 set -- $line
	 dest="$1"
	 port="$2"

	 rsync -av -e "ssh -p $port" "$PRP/" "$dest"
 done < "$SERVER_LIST"
