import os
import subprocess

def execute(cmd, args, session, state):
    print(args)
    subprocess.run("cd", shell=True)
