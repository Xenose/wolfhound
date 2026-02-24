import os
import argparse
import subprocess

from pathlib import Path


def execute(sh, cmd, args):
    parser = argparse.ArgumentParser(
        prog='run',
        description='runs one of the compiled executables.',
        epilog='Text')

    parser.add_argument('BIN', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)
    p = Path(sh.session["home"], "build", "bin", a.BIN[0])

    # Running the sub command
    pfd = subprocess.Popen(p, stdout=subprocess.PIPE)
    pfd.wait()
