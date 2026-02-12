import shutil

from common.compiler import compiler


def execute(cmd, args, session, state, prompt):
    state["compiler"] = {
        "name": "icx",
        "c": shutil.which("icx"),
        "cxx": shutil.which("icpx"),
    }

    compiler(state, args)
