import os
import subprocess

def execute(cmd, args, session, state):
    subprocess.run(args, check=False)
