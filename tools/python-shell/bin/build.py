import os
import subprocess


def execute(cmd, args, session, state, prompt):
    if "compiler" not in state:
        print("No compiler selected!")
        return

    target = "{}-{}-{}-{}".format(
        state['compiler']['name'],
        state['compiler']['build-system'],
        state['platform'],
        state['compiler']['arch']
    ).lower()

    path = f"build/{target}"

    if not os.path.exists("build"):
        os.mkdir("build")

    if not os.path.exists(path):
        os.mkdir(path)

    print("Configuring cmake...")
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
                "-G", state['compiler']["build-system"],
                f"-DCMAKE_C_FLAGS='--target={state['compiler']["arch"]}'",
                f"-DCMAKE_CXX_FLAGS='--target={state['compiler']["arch"]}'",
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
