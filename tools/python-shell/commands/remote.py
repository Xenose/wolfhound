import argparse

from common.params import params_c


def execute(params: params_c):
    parser = argparse.ArgumentParser(
        prog='cd',
        description='change to remote execution.',
        epilog='Text')

    parser.add_argument("-l", "--listen", default="127.0.0.1")
    parser.add_argument("-p", "--port", default="8000")

    a = parser.parse_args(params.args)

    params.sh.builder.set_mode("remote", a.lislistenn, a.port)
