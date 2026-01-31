import os
import sys
import subprocess


def code_build():
    print("Building code")


def cmd_clear():
    subprocess.run(["clear"])

def cmd_exit():
    sys.exit(0)

def cmd_ls():
    out = subprocess.run(['ls'])


commands = {
    "build": code_build,

    "clear": cmd_clear,
    "exit": cmd_exit,
    "ls": cmd_ls
}


while True:
    cmd = input("wh-shell> ")

    if cmd in commands:
        commands[cmd]()
