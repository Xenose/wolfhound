import subprocess


def execute(cmd, args):
    print("building...")
    # Remove hard coded target
    subprocess.run(
            "cmake --build 'build/clang-Android-aarch64'",
            shell=True
        )
