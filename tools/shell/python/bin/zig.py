import shutil

from common.compiler import compiler


def execute(cmd, args, session, state):
    state["compiler"] = {
        "name": "zig",
        "c": "zig cc",
        "cxx": None,
    }

    compiler(state, args)
