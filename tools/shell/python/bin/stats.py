import os
import subprocess


def execute(cmd, args, session, state):
    match os.name:
        case 'nt':
            print("Windows stats not supported!")
        case _:
            subprocess.run("cloc --exclude-dir=build --force-lang=C,h --force-lang=C++,hpp --fmt=2 .", shell=True)
