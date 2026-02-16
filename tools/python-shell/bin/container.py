import os
import shutil
import subprocess
import argparse
import platform
from pathlib import Path


def execute(sh, cmd, args):
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

    a = parser.parse_args(args)
    # Container Image Path
    cip = Path(
        sh.session["home"],
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
            f"{sh.session["home"]}"
        ])
# docker run --gpus all --rm -it -v "$PWD":/wolfhound "test_image_wolfhound"
# docker rmi "test_image_wolfhound"

        subprocess.run([
            "docker",
            "run",
            "--rm",  # Remove the image
            "-it",   # Sets the shell to be interactive
            "-v", f"{sh.session["home"]}:/project",
            f"test_image_{a.NAME[0]}"
        ])
    else:
        print("No supported container agent found!")
