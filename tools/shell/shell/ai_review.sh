#!/bin/bash

set -e

MODEL="qwen2.5-coder:latest"
PROMT="You are a code reviewer for this code, don't write the code, don't list key points, give clear feed back and file and line number with the suggestion."

cd "${PRP}"
cat "${@}" | ollama run "${MODEL}" "${PROMT}"
