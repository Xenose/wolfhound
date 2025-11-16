FROM fedora:latest

ENV TERM=xterm-256color
ENV LANG=C.UTF-8

COPY tools/packages/fedora.packages /tmp/

RUN dnf update -y
RUN cat /tmp/fedora.packages | dnf install -y

ENTRYPOINT ["/bin/bash"]
