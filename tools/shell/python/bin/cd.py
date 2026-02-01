import os
import subprocess

def execute(cmd, args):
    print(args)
    subprocess.run("cd", shell=True)
