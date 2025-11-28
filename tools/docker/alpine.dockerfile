FROM alpine:latest

ENV TERM xterm-256color
ENV LANG C.UTF-8


RUN apk upgrade
RUN apk add \
		 build-base \
		 linux-headers \
		 cmake \
		 clang \
		 ninja \
		 git \
		 python3 \
		 lua5.4 \
		 libunwind-dev \
		 sdl3-dev \
		 glfw-dev \
		 glew-dev \
		 vulkan-headers \
		 vulkan-validation-layers \
		 pkgconf \
		 neovim \
		 cloc \
		 zsh \
		 libbsd-dev

WORKDIR /wolfhound

ENTRYPOINT ["/bin/ash"]
