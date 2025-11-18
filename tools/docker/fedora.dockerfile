FROM fedora:latest

ENV TERM=xterm-256color
ENV LANG=C.UTF-8

COPY tools/packages/fedora.packages /tmp/fedora.packages

RUN dnf update -y
RUN dnf install -y $(tr '\n' ' ' < /tmp/fedora.packages)

ENTRYPOINT ["/bin/bash"]
