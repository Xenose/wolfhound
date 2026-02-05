import os
import subprocess


def execute(cmd, args, session, state):
    match os.name:
        case 'nt':
            subprocess.run("cls")
        case _:
            subprocess.run("clear")
