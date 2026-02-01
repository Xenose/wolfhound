import os

def execute(cmd, args):
    dirs = ""
    files = ""

    for x in os.scandir():
        if x.is_dir():
            dirs += f"\033[91m{x.name}\033[0m "
        if x.is_file():
            files += f"{x.name} "

    print(f"{dirs} {files}")
    pass
