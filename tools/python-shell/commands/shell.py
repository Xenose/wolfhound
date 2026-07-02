import subprocess

from common.params import params_c


def execute(params: params_c):
    subprocess.run(params.args, check=False)
