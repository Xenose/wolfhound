import argparse
import os
import platform
import shutil

def compiler(state, args):
    parser = argparse.ArgumentParser(
        prog='clang selector',
        description='What the program does',
        epilog='Text at the bottom of help'
    )

    parser.add_argument("--arch", help="Set the architecture")
    parser.add_argument("--build-system", help="Set the build system to use")

    a = parser.parse_args(args)

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

    if a.build_system:
        match a.build_system.lower():
            case "ninja":
                state["build-system"] = "Ninja"
            case "make":
                if "posix" == os.name:
                    state["build-system"] = "Unix Makefiles"
                elif "nt" == os.name:
                    state["build-system"] = "NMake Makefiles"
            case _:
                print(f"Unknown build system: {a.build_system}, keeping previous value")
    else:
        if "build-system" not in state.keys():
            print(f"No build system inputed, defaulting to [ Ninja ]")
            state["build-system"] = "ninja"
        else:
            print(f"No build system inputed, keeping previous value")

