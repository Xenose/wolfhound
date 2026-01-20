FROM alpine:latest

ENV TERM xterm-256color
ENV LANG C.UTF-8


RUN apk upgrade
RUN apk add $(tr '\n' ' ' < /tmp/fedora.packages)

WORKDIR /wolfhound

ENTRYPOINT ["/bin/ash"]
