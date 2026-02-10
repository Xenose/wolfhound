import shutil

from common.compiler import compiler


def execute(cmd, args, session, state):
    state["compiler"] = {
        "name": "gcc",
        "c": shutil.which("cl"),
        "cxx": shutil.which("cl"),
    }

    compiler(state, args)
