#!/bin/sh

if uname -o >/dev/null 2>&1; then
	os=$(uname -o)

	if [ -z "${os}" ]; then
		os=$(uname -s)
	fi
else
	os=$(uname -s)
fi

printf "%s-%s\n" "${os}" "$(uname -m)" | tr ' ' '-' | tr '/' '-'
