import os
import subprocess


def execute(cmd, args, session, state):
    print("building...")
    target = f"{state["compiler"]["name"]}-{state["platform"]}-{state["arch"]}"
    path = f"build/{target}"

    if not os.path.exists(path):
        os.mkdir(path, exist_ok=True)

    # Remove hard coded target
    subprocess.run(
        f"""
            cmake -S '.' -B '{path}' \
                -DCMAKE_C_COMPILER='{state['compiler']['c']}' \
                -DCMAKE_CXX_COMPILER='{state['compiler']['cxx']}'
        """,
        shell=True,
        check=True
    )

    subprocess.run(
        f"cmake --build '{path}'",
        shell=True,
        check=True
    )
