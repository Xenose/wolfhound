FROM archlinux:latest

ENV TERM xterm-256color
ENV LANG C.UTF-8

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm \
	base-devel \
	cmake \
	clang \
	ninja \
	git \
	python \
	lua \
	libunwind \
	sdl3 \
	glfw \
	glew \
	vulkan-headers \
	vulkan-validation-layers \
	pkgconf \
	neovim \
	cloc \
	zsh \
	libbsd

RUN useradd -m dev
USER dev
WORKDIR /home/dev/wolfhound
