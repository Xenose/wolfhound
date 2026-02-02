import os
import sys
import json
import subprocess
import importlib
import argparse

from prompt_toolkit import PromptSession
from prompt_toolkit.completion import Completer, Completion
from pathlib import Path

class file_completer_c(Completer):
    def __init__(self, dir):
        self.dir = Path(dir)

    def get_completions(self, doc, c_event):
        text = doc.text

        for f in self.dir.glob("*.py"):
            if f.name.startswith(text):
                yield Completion(f.name.removesuffix(".py"), start_position=-len(text))

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
        return

    mod.execute(cmd, args, session, state)
# end def dispatch


# Setting up the session
session = {
    "exit": False
}
ps = PromptSession();
pc = file_completer_c(dir="tools/shell/python/bin")

if os.path.exists(".wolfhound/state.json"):
    print("State found")
    with open(".wolfhound/state.json", "r") as fd:
        state = json.loads(fd.read())
else:
    print("No state found creating one")
    state = {}


# Main loop
while not session["exit"]:
    cmd = ps.prompt("wh-shell> ", completer=pc)

    if not cmd:
        continue

    cmd = cmd.strip().split()

    try:
        dispatch(cmd[0], cmd[1:], session, state)
    except argparse.ArgumentError as e:
        print(f"Command failed! {e}")
    except SystemExit:
        pass
