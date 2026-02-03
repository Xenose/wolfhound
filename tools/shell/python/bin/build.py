import os
import subprocess


def execute(cmd, args, session, state):
    if "compiler" not in state:
        print("No compiler selected!")
        return

    target = f"{state['compiler']['name']}-{state['platform']}-{state['arch']}"
    path = f"build/{target}"

    if not os.path.exists(path):
        os.mkdir(path)

    # Remove hard coded target
    subprocess.run([
            "cmake",
            "-S", ".",
            "-B", path,
            f"-DCMAKE_C_COMPILER={state['compiler']['c']}",
            f"-DCMAKE_CXX_COMPILER={state['compiler']['cxx']}",
        ],
        check=True
    )

    subprocess.run(
        f"cmake --build '{path}'",
        shell=True,
        check=True
    )
