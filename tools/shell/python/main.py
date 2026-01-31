import os
import sys
import subprocess

if os.name == "nt"
    CMD_CLEAR="cls"
    CMD_LS="dir"
else
    CMD_CLEAR="clear"
    CMD_LS="ls"

def code_build():
    print("Building code")


def cmd_clear():
    subprocess.run([CMD_CLEAR])

def cmd_exit():
    sys.exit(0)

def cmd_ls():
    out = subprocess.run([CMD_LS])


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
