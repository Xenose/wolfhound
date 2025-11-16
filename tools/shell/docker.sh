#!/bin/sh

set -e

#-e XDG_RUNTIME_DIR=/tmp \
#-v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/$WAYLAND_DISPLAY" \

#docker run --rm -it \
#	-e XDG_RUNTIME_DIR="$XDG_RUNTIME_DIR" \
#	-e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" \
#	-e DISPLAY="$DISPLAY" \
#	-v "$XDG_RUNTIME_DIR:$XDG_RUNTIME_DIR:ro" \
#	-v "${PRP}":/wolfhound \
#	--user="$(id -u):$(id -g)" \
#	"${1}" /bin/bash

__wh_docker() {
	docker build -t "test_image_wolfhound" -f "${PRP}/tools/docker/${1}.dockerfile" "${PRP}"
	docker run --rm -it -v "$PWD":/wolfhound "test_image_wolfhound"
	docker rmi "test_image_wolfhound"
}
