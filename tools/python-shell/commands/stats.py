import os
import subprocess

from common.params import params_c


def execute(params: params_c):
    exlude_dirs = "build"

    match os.name:
        case 'nt':
            print("Windows stats not supported!")
        case _:
            subprocess.run([
                "cloc",
                "--exclude-dir", f"{exlude_dirs}",
                "--force-lang", "C,h",
                "--force-lang", "C++,hpp",
                "--fmt", "2",
                "."
            ])
