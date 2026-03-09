import os
import uuid
import argparse
import datetime
import json

from pathlib import Path

from common.utils import path_complete
from prompt_toolkit import print_formatted_text, ANSI

def complete(text):
    if text.startswith('-'):
        return [
            "-f", "--force",
            "-r", "--recursive",
            "--restore",
            "--trash",
        ]

    return path_complete(text)



def add_record(filepath):
    return {
        "filepath": filepath,
        "time": str(datetime.datetime.now()),
        "UUID": str(uuid.uuid4())
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

    record_path = Path(".wolfhound", "trash.json")

    if record_path.exists():
        with open(record_path, "r") as fd:
            record = json.loads(fd.read())
    else:
        record = {
            "items": []
        }

    for r in a.PATH:
        path = Path(r)
        filepath = str(path.absolute())

        if path.is_dir() and not a.recursive:
            print(f"The given file is a directory for removing it use -r [ {filepath}")
            continue

        record["items"].append(add_record(filepath))

    print(record)
    with open(record_path, "w") as fd:
        json.dump(record, fd, indent=4)
        fd.write("\n")
