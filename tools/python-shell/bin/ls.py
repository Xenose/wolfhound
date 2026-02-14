import os
import argparse
from prompt_toolkit import print_formatted_text, ANSI


def long(files, dirs, x):
    if x.is_dir():
        dirs.append(f"\033[91m{x.name}\033[0m")
    elif x.is_file():
        files.append(f"{x.name}")


def short(files, dirs, x):
    if x.is_dir():
        # return f"\033[91m{x.name}\033[0m "
        dirs.append(f"\033[91m{x.name}\033[0m")
    elif x.is_file():
        files.append(f"{x.name}")


def execute(sh, cmd, args):
    dirs = []
    files = []
    path = '.'

    parser = argparse.ArgumentParser(
        prog='ls',
        description='list the items in a directory',
        epilog='Text')

    parser.add_argument("-l", "--long", action='store_true', help="list view")
    parser.add_argument("-a", "--all", action='store_true', help="list view")
    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)

    if a.long:
        sp = '\n'
        func = long
    else:
        sp = ' '
        func = short

    if 0 < len(a.PATH):
        path = a.PATH[0]

    for x in os.scandir(path):
        if x.name.startswith('.') and not a.all:
            continue

        func(files, dirs, x)

    print_formatted_text(ANSI(f"{sp.join(dirs + files)}"))
