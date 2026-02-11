import shutil

from common.compiler import compiler


def execute(cmd, args, session, state, prompt):
    state["compiler"] = {
        "name": "tcc",
        "c": shutil.which("tcc"),
        "cxx": None,
    }

    compiler(state, args)
