#!/bin/bash

set -e

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" > /dev/null && pwd )"
ENGINE_DIR="$(dirname "${SCRIPT_DIR}")"

cd "${ENGINE_DIR}"


if command pacman > /dev/null; then
	pacman -S "$(cat "${ENGINE_DIR}/packages/arch.pkgs")"
fi
