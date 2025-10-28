#!/bin/bash

set -e

MODEL="qwen2.5-coder:latest"
PROMT="You are a code reviewer for this code, the input might be more then one file."

cd "${PRP}"
cat "README.md" "${@}" | ollama run "${MODEL}" "${PROMT}"
