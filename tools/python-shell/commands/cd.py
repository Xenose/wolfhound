import os
import argparse

from pathlib import Path
from common.params import params_c
from common.utils import path_complete


def complete(text=None):
    if text.startswith('-'):
        return [
        ]

    return path_complete(text, only_dir=True)


def execute(params: params_c):
    parser = argparse.ArgumentParser(
        prog='cd',
        description='change the current working directory',
        epilog='Text')

    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(params.args)

    path = Path(a.PATH[0])

    if not path.is_dir():
        print(f"cd: not a directory: {path}")
        return

    if 0 < len(path.name):
        os.chdir(path)
    else:
        os.chdir(params.sh.session["home"])
    # subprocess.run("cd", shell=True)
