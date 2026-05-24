import os
import argparse
import subprocess

from common.utils import path_complete
from pathlib import Path


def complete(text=None):
    return path_complete(text)


def execute(sh, cmd, args):
    path = os.getcwd()
    parser = argparse.ArgumentParser(
        prog='run',
        description='runs one of the compiled executables.',
        epilog='Text')

    parser.add_argument('BIN', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)
    p = Path(sh.session["home"], path, a.BIN[0])

    # Running the sub command
    pfd = subprocess.Popen(p, stdout=subprocess.PIPE)
    pfd.wait()
