import os
import shutil

from common.compiler import compiler


def execute(cmd, args, session, state, prompt):
    if "nt" != os.name:
        print("msvc is only supported on windows!")
        return

    state["compiler"] = {
        "name": "msvc",
        "c": shutil.which("cl"),
        "cxx": shutil.which("cl"),
    }

    compiler(state, args)
