import os
import argparse
import platform
import shutil

from common.compiler import compiler

def execute(cmd, args, session, state):
    state["compiler"] = {
        "name": "gcc",
        "c": shutil.which("gcc"),
        "cxx": shutil.which("g++"),
    }

    compiler(state, args)
