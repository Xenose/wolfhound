import os
import argparse

from pathlib import Path
from common.params import params_c


def execute(params: params_c):
    parser = argparse.ArgumentParser(
        prog='touch',
        description='',
        epilog='Text')

    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(params.args)
    path = Path(a.PATH[0])

    if path.exists():
        # TODO update timestamp
        print("File exists...")
    else:
        with open(path, "w") as _:
            pass
