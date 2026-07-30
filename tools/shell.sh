#!/bin/sh

set -e

# Checks if python is installed, otherwise exits.
if ! command -v python3 > /dev/null; then
	echo "Please install python!"
	exit 1
fi

# Some shells have issues with getting there base path,
# for example docker doesn't work neither does ash.
if [ -n "$ANDROID__BUILD_VERSION_SDK" ] || [ "$(basename "$SHELL")" = "ash" ]; then
	echo "Running inside Android/Ash Shell, using current path instead!"
	WP=$(pwd)
else
	# Detecting the script path
	WP="$(cd -- "$(dirname -- "$0")" && pwd)"
	echo "Shell supported, setting base path to [ ${WP} ]"

	# Checks if the path is the tools path
	case "$WP" in
		*/tools) WP=$(dirname "$WP") ;;
	esac
fi

if [ ! -f "${WP}/tools/shell.sh" ]; then
	echo "Not in the wolfhound directory ABORTING!"
	exit 1
fi

cd "${WP}"

if [ ! -d .venv ]; then
    python3 -m venv .venv
else
    echo "Using existing virtual environment"
fi

# Using posix source over source for alpine and termux
. .venv/bin/activate

pip3 install prompt-toolkit
python3 "$WP/tools/python-shell/main.py"
