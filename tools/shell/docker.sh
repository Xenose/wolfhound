#!/bin/sh

set -e

#-e XDG_RUNTIME_DIR=/tmp \
#-v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/$WAYLAND_DISPLAY" \

docker run --rm -it \
	-e XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" \
	-e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" \
	-e DISPLAY="$DISPLAY" \
	-v "$XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR:ro" \
	-v "${PRP}":/wolfhound \
	--user="$(id -u):$(id -g)" \
	"${1}" /bin/bash 
