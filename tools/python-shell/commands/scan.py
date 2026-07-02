from common.utils import find_executable

from common.params import params_c


def execute(params: params_c):
    print(find_executable("build", [
        "CMake",
        "CMakeFiles"
    ]))
