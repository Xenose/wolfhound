import argparse
import os
import platform
# import shutil


class compiler_c:
    def __init__():
        pass


conf_compiler = {
    "clang": {
        "windows": {
            "x64": "x86_64-pc-windows-gnu"
        },

        "linux": {
            "x64": "x86_64-linux-gnu",
            "wasm64": "wasm64-unknown-unknown"
        },
    },

    "gcc": {
        "linux": {
            "x64": "x86_64-linux-gnu"
        },
    }
}


def get_platform():
    out = None

    if "android" in platform.platform():
        out = "android"
    else:
        out = platform.uname().system.lower()

    return out


def get_arch(args, state):
    if args.arch:
        arch = args.arch.lower()
    else:
        arch = "x64"

    out = conf_compiler[state["compiler"]["name"]][platform.system().lower()][arch]

    # if args.arch:
    #     match args.arch.lower():
    #         case "x64":
    #             if "clang" == state["compiler"]["name"] and "nt" == os.name:
    #                 out = ""
    #             else:
    #                 out = X64
    #         case "arm64":
    #             out = "aarch64"
    #         case "w64":
    #             out = "wasm64"
    #         case _:
    #             print(f"Unknown architecture: {a.arch}, keeping previous value")
    # else:
    #     if "clang" == state["compiler"]["name"] and "nt" == os.name:
    #         out = "x86_64-pc-windows-gnu"
    #     else:
    #         out = X64

    return out


def get_build_system(args, state):
    out = None

    if args.build_system:
        match args.build_system.lower():
            case "ninja":
                out = "Ninja"
            case "make":
                if "posix" == os.name:
                    out = "Unix Makefiles"
                elif "nt" == os.name:
                    out = "NMake Makefiles"
            case _:
                print("Unknown build system: {}, keeping previous value".format(out.build_system))
    else:
        if "build-system" not in state.keys():
            print("No build system inputed, defaulting to [ Ninja ]")
            out = "Ninja"
        else:
            print("No build system inputed, keeping previous value")

    return out


def compiler(state, args):
    parser = argparse.ArgumentParser(
        prog='clang selector',
        description='What the program does',
        epilog='Text at the bottom of help'
    )

    parser.add_argument("--arch", help="Set the architecture")
    parser.add_argument("--build-system", help="Set the build system to use")

    a = parser.parse_args(args)

    state["platform"] = get_platform()
    state["compiler"]["arch"] = get_arch(a, state)
    state["compiler"]["build-system"] = get_build_system(a, state)

