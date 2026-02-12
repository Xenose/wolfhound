import os
import argparse


def execute(cmd, args, session, state, prompt):
    parser = argparse.ArgumentParser(
        prog='touch',
        description='',
        epilog='Text')

    parser.add_argument('PATH', nargs=argparse.REMAINDER)

    a = parser.parse_args(args)

    if os.path.exists(a.PATH[0]):
        # TODO update timestamp
        print("File exists...")
    else:
        with open(a.PATH[0], "w") as fd:
            pass

