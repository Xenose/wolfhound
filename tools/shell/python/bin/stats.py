import os
import subprocess


def execute(cmd, args, session, state):
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
