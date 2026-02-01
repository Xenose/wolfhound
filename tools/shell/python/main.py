import os
import sys
import json
import subprocess
import importlib


def dispatch(cmd, args, session, state):
    mod = None
    # print(f"{cmd}")

    try:
        mod = importlib.import_module(f"bin.{cmd}")
    except ImportError:
        print(f"Unknown commnad: {cmd}")
        return

    if not hasattr(mod, "execute"):
        print(f"{cmd}: invalid command module")

    mod.execute(cmd, args, session, state)
# end def dispatch


# Setting up the session
session = {}

if os.path.exists(".wolfhound/state.json"):
    print("State found")
    with open(".wolfhound/state.json", "r") as fd:
        state = json.loads(fd.read())
else:
    print("No state found creating one")
    state = {}


# Main loop
while True:
    cmd = input("wh-shell> ").strip().split(" ")

    try:
        dispatch(cmd[0], cmd[1:], session, state)
    except Exception as e:
        print(f"Command failed! {e}")
