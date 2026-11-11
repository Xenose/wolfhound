#!/bin/sh

# TODO check make the script use the script path instead!
uvicorn ci:app --reload --app-dir tools/python-shell --host 0.0.0.0
