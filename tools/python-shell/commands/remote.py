import argparse

from common.params import params_c
from common.server import server_c


def execute(params: params_c):
    parser = argparse.ArgumentParser(
        prog='cd',
        description='change to remote execution.',
        epilog='Text')

    parser.add_argument("-s", "--servers", default="127.0.0.1:6666:default")

    a = parser.parse_args(params.args)

    servers = []

    for server in a.servers.split(","):
        for item in server.split(":"):
            ip = "127.0.0.1"
            port = "6666"
            name = "default"

            if item[0] is not None:
                ip = item[0]

            if item[1] is not None:
                port = item[1]

            if item[2] is not None:
                name = item[2]

            servers.append(server_c(ip, port, name))

    params.sh.builder.set_mode("remote", servers)
