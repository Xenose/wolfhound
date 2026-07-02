import os
import shutil
import subprocess
import argparse
import platform
from pathlib import Path

from common.params import params_c


def execute(params: params_c):
    os_name = platform.system().lower()

    if "linux" != os_name:
        print(f"Container is only supported on Linux! Not {os_name}")
        return

    parser = argparse.ArgumentParser(
        prog='container',
        description='change the current working directory',
        epilog='Text')

    parser.add_argument('--fresh', default=False)
    parser.add_argument('NAME', nargs=argparse.REMAINDER)

    a = parser.parse_args(params.args)

    # Container Image Path
    cip = Path(
        params.sh.session["home"],
        "tools",
        "docker",
        f"{a.NAME[0]}.dockerfile"
    )

    if not os.path.exists(cip):
        print("No docker file found")

    if shutil.which("docker"):
        subprocess.run([
            "docker",
            "build",
            "-t", f"test_image_{a.NAME[0]}",
            "-f", cip,
            f"{params.sh.session["home"]}"
        ])
# docker run --gpus all --rm -it -v "$PWD":/wolfhound "test_image_wolfhound"
# docker rmi "test_image_wolfhound"

        subprocess.run([
            "docker",
            "run",
            "--rm",  # Remove the image
            "-it",   # Sets the shell to be interactive
            "-v", f"{params.sh.session["home"]}:/project",
            f"test_image_{a.NAME[0]}"
        ])
    else:
        print("No supported container agent found!")
