FROM alpine:latest

ENV TERM=xterm-256color
ENV LANG=C.UTF-8

COPY packages/alpine.packages /tmp/alpine.packages

RUN apk upgrade
RUN apk add $(tr '\n' ' ' < /tmp/alpine.packages)

WORKDIR /project

ENTRYPOINT ["/bin/ash"]
