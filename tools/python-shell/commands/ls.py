import os
import argparse
from pathlib import Path

if "nt" != os.name:
    import pwd
    import grp

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
        files.append(f"\033[92m{x.name:30}\033[0m {user_name}:{group_name:10}")
    elif x.is_file():
        files.append(f"{x.name:30} {user_name}:{group_name:10} {stat.st_size}")


def short(files, dirs, x):
    if x.is_dir():
        # return f"\033[91m{x.name}\033[0m "
        dirs.append(f"\033[91m{x.name}\033[0m")
    elif x.is_symlink():
        files.append(f"\033[92m{x.name:30}\033[0m")
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

    p = Path(text)

    if text.endswith(os.sep):
        parent = p
        prefix = ''
    else:
        if p.parent.exists():
            parent = p.parent
        else:
            parent = Path(".")

        prefix = p.name

    try:
        return [
            str(x) + ('/' if x.is_dir() else '')
            for x in parent.iterdir()
            if x.name.startswith(prefix)
        ]
    except FileNotFoundError:
        return []


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
