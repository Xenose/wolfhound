#!/bin/bash
# This script is only used to push "in rapid development" branch only.

set -e

branch=$(git symbolic-ref --short HEAD)

if [ "inrdev" = "${branch}" ]; then
	echo "On 'inrdev' branch. Pulling latest changes and committing..."
	git pull
	git add -A

	if ! git diff --cached --quiet; then
		git commit -m "inrdev"
		git push origin "${branch}"
	else
		echo "No staged changes to commit."
	fi
else
	echo "You are not on the 'inrdev' branch. Aborting push."
	exit 1
fi
