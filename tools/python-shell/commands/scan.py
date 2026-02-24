from common.utils import find_executable


def execute(sh, cmd, args):
    print(find_executable("build", [
        "CMake",
        "CMakeFiles"
    ]))
