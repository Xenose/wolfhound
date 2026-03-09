import os
import argparse

from pathlib import Path

def execute(sh, cmd, args):
    parser = argparse.ArgumentParser(
        prog='touch',
        description='',
        epilog='Text')

    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)
    path = Path(a.PATH[0])

    if path.exists():
        # TODO update timestamp
        print("File exists...")
    else:
        with open(path, "w") as _:
            pass
