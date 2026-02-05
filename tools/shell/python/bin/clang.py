import shutil

from common.compiler import compiler


def execute(cmd, args, session, state):
    state["compiler"] = {
        "name": "clang",
        "c": shutil.which("clang"),
        "cxx": shutil.which("clang++"),
    }

    compiler(state, args)
