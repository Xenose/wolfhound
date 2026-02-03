import os
import subprocess
import argparse

def execute(cmd, args, session, state):
    parser = argparse.ArgumentParser(
        prog='cd',
        description='change the current working directory',
        epilog='Text')

    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)

    #print(a.rest[0])

    if 0 < len(a.PATH):
        os.chdir(a.PATH[0])
    else:
        os.chdir(session["home"])
    # subprocess.run("cd", shell=True)
