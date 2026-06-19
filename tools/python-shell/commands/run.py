import os
import argparse
import subprocess
import time

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
    parser.add_argument("-t", "--time", action='store_true', help="list view")

    a = parser.parse_args(args)
    p = Path(sh.session["home"], path, a.BIN[0])

    # Running the sub command
    # TODO :: Improve this is a hack to pass flags

    if a.time:
        exec_time = time.perf_counter_ns()

    subprocess.run([str(p)] + a.BIN[1:])

    if a.time:
        exec_time = time.perf_counter_ns() - exec_time

        ms = int(exec_time * 0.000001)
        ns = int(exec_time - (ms / 0.000001))

        print("ms {} ns {}".format(ms, ns))
