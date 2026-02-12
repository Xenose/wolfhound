import shutil

from common.compiler import compiler


def execute(cmd, args, session, state, prompt):
    state["compiler"] = {
        "name": "zig",
        "c": "zig cc",
        "cxx": None,
    }

    compiler(state, args)
