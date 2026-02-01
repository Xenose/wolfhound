import os
import argparse
import platform

def execute(cmd, args, session, state):
    parser = argparse.ArgumentParser(
        prog='clang selector',
        description='What the program does',
        epilog='Text at the bottom of help')

    parser.add_argument("--arch", help="Set the architecture")

    a = parser.parse_args(args)

    state["compiler"] = "clang"
    state["platform"] = platform.uname().system.lower()

    if a.arch:
        match a.arch.lower():
            case "x64":
                state["arch"] = "x64"
            case "arm64":
                state["arch"] = "aarch64"
            case "w64":
                state["arch"] = "wasm64"
            case _:
                print(f"Unknown architecture: {a.arch}, keeping previous value")
    else:
        state.setdefault("arch", "x64")
