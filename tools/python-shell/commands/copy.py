import os
import argparse
import pyperclip

from common.utils import path_complete
from common.params import params_c


def complete(text=None):
    return path_complete(text)


def execute(params: params_c):
    print("Copying...")

    text = ""
    path = os.getcwd()
    parser = argparse.ArgumentParser(
        prog='copy',
        description='copies files to clipboard',
        epilog='Text')

    parser.add_argument('FILES', nargs=argparse.REMAINDER)

    a = parser.parse_args(params.args)

    for f in a.FILES:
        with open(f) as fd:
            text += fd.read()

    pyperclip.copy(text)

   # p = Path(sh.session["home"], path, a.BIN[0])

   # # Running the sub command
   # pfd = subprocess.Popen(p, stdout=subprocess.PIPE)
   # pfd.wait()
