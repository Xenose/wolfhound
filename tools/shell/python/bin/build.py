import os
import subprocess


def execute(cmd, args, session, state):
    print("building...")
    target = f"{state["compiler"]}-{state["platform"]}-{state["arch"]}"
    path = f"build/{target}"

    if not os.path.exists(path):
        os.mkdir(path, exist_ok=True)

    # Remove hard coded target
    subprocess.run(
        f"cmake -S '.' -B '{path}'",
        shell=True,
        check=True
    )

    subprocess.run(
        f"cmake --build '{path}'",
        shell=True,
        check=True
    )
