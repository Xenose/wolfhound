import os
import subprocess

from common.params import params_c


def execute(params: params_c):
    match os.name:
        case 'nt':
            subprocess.run("cls", shell=True)
        case _:
            subprocess.run("clear")
