#!/bin/sh

set -eu
SERVER_LIST="${PRP}/.wolfhound/servers"

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

	 set +e
	 rsync --exclude ".wolfhound" -qav -e "ssh -p $port" "$PRP/" "$dest"
	 set -e
 done < "$SERVER_LIST"
