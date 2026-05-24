import os
import argparse

if "nt" != os.name:
    import pwd
    import grp

from common.utils import path_complete
from prompt_toolkit import print_formatted_text, ANSI


def long(files, dirs, x):
    stat = x.stat()

    if "nt" != os.name:
        pw = pwd.getpwuid(stat.st_uid)
        gr = grp.getgrgid(stat.st_gid)

        user_name = pw.pw_name
        group_name = gr.gr_name
    else:
        user_name = ""
        group_name = ""

    if x.is_dir():
        dirs.append(f"\033[91m{x.name}\033[0m")
    elif x.is_symlink():
        files.append(f"\033[92m{x.name:50}\033[0m {user_name}::{group_name:10}")
    elif x.is_file():
        files.append(f"{x.name:50} {user_name}::{group_name:10} {stat.st_size}")


def short(files, dirs, x):
    if x.is_dir():
        # return f"\033[91m{x.name}\033[0m "
        dirs.append(f"\033[91m{x.name}\033[0m")
    elif x.is_symlink():
        files.append(f"\033[92m{x.name}\033[0m")
    elif x.is_file():
        files.append(f"{x.name}")


def complete(text=None):
    if text.startswith('-'):
        return [
            '-a',
            '-l',
            '-la',
            '--all',
            '--long'
        ]

    return path_complete(text)


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

    if not os.path.isdir(path):
        files = [path]
    else:
        for x in os.scandir(path):
            if x.name.startswith('.') and not a.all:
                continue
            func(files, dirs, x)

    dirs.sort()
    files.sort()

    print_formatted_text(ANSI(f"{sp.join(dirs + files)}"))
