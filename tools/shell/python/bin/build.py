import os
import subprocess


def execute(cmd, args, session, state):
    if "compiler" not in state:
        print("No compiler selected!")
        return

    target = f"{state['compiler']['name']}-{state['platform']}-{state['arch']}"
    path = f"build/{target}"

    if not os.path.exists("build"):
        os.mkdir("build")

    if not os.path.exists(path):
        os.mkdir(path)

    if "zig" == state["compiler"]["name"]:
        subprocess.run(
            f"CC='{state['compiler']['c']}' cmake -S . -B {path}",
            shell=True,
            check=True
        )
    else:
        subprocess.run([
                "cmake",
                "-S", ".",
                "-B", path,
                f"-DCMAKE_C_COMPILER={state['compiler']['c']}",
                f"-DCMAKE_CXX_COMPILER={state['compiler']['cxx']}",
            ],
            check=True
        )

    subprocess.run([
            "cmake",
            "--build", f"{path}"
        ],
        check=True
    )
