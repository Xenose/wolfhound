import os
import subprocess


def execute(sh, cmd, args):
    match os.name:
        case 'nt':
            subprocess.run("cls", shell=True)
        case _:
            subprocess.run("clear")
