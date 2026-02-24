import os
import uuid
import argparse
import datetime


def complete():
    return [
        "-r", "--recursive",
        "--trash",
    ]


def add_record(filename):
    return {
        "filename": filename,
        "time": str(datetime.datetime.now()),
        "UUID": uuid.uuid4()
    }


def execute(sh, cmd, args):
    parser = argparse.ArgumentParser(
        prog='ls',
        description='list the items in a directory',
        epilog='Text')

    parser.add_argument("-r", "--recursive", action='store_true', help="list view")
    parser.add_argument("--trash", action='store_true', help="list view")
    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)

    if 0 == len(a.PATH):
        return

    if os.path.isdir(a.PATH[0]) and not a.recursive:
        print(f"The given file is a directory for removing it use -r [ {a.PATH[0]}")
    else:
        print(f"Removing {add_record(a.PATH[0])}")
        pass
