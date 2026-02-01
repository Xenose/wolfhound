import os
import sys
import subprocess
import importlib


if os.name == "nt":
    CMD_CLEAR="cls"
    CMD_LS="dir"
else:
    CMD_CLEAR="clear"
    CMD_LS="ls"


def code_build():
    print("Building code")


def cmd_clear():
    subprocess.run([CMD_CLEAR], shell=True)

def cmd_exit():
    sys.exit(0)

def cmd_ls():
    out = subprocess.run([CMD_LS], shell=True)


commands = {
    "build": code_build,

    "clear": cmd_clear,
    "exit": cmd_exit,
    "ls": cmd_ls
}


def dispatch(cmd, args):
    mod = None
    print(f"{cmd}")

    try:
        mod = importlib.import_module(f"bin.{cmd}")
    except ImportError:
        print(f"Unknown commnad: {cmd}")
        return

    if not hasattr(mod, "execute"):
        print(f"{cmd}: invalid command module")

    mod.execute(cmd, args)


while True:
    cmd = input("wh-shell> ").strip()

    dispatch(cmd, None)

    # if cmd in commands:
    #    commands[cmd]()
