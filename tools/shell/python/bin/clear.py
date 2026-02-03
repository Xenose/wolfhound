import os
import subprocess

def execute(cmd, args, session, state):
    match os.name:
        case 'nt':
            subprocess.run("cls", shell=True)
        case _:
            subprocess.run("clear", shell=True)
