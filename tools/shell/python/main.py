import os
import json
import importlib
import argparse
import getpass

from prompt_toolkit import PromptSession, ANSI
from prompt_toolkit.completion import Completer, Completion
from pathlib import Path


class file_completer_c(Completer):
    def __init__(self, dir):
        self.dir = Path(dir)

    def get_completions(self, doc, c_event):
        text = doc.text

        for f in self.dir.glob("*.py"):
            if f.name.startswith(text):
                yield Completion(
                    f.name.removesuffix(".py"),
                    start_position=-len(text)
                )


def dispatch(cmd, args, session, state, prompt):
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

    mod.execute(cmd, args, session, state, prompt)
# end def dispatch


# Setting up the session
session = {
    "exit": False,
    "home": os.getcwd(),
}

# The prompt_toolkit's context
ps = PromptSession()
pc = file_completer_c(dir="tools/shell/python/bin")

if os.path.exists(".wolfhound/state.json"):
    print("State found")
    with open(".wolfhound/state.json", "r") as fd:
        state = json.loads(fd.read())
else:
    print("No state found creating one")
    state = {}

welcome = """

   Welcome to wolfhound shell, this shell
   is designed to be familiar but its not
   POSIX, the commands maybe looks the same
   but they are not the same.

   To get started type help for information.
"""

# We clear the screen before the welcome message.
dispatch("clear", None, session, state, ps)
print(welcome)

# Main loop
while not session["exit"]:
    current_dir = "/".join(os.getcwd().split(os.sep)[-3:]) or "/"
    cmd = ps.prompt(ANSI(f"\n{getpass.getuser()}@{current_dir}\n\033[32mwh-shell>\033[0m "), completer=pc)

    if not cmd:
        continue

    cmd = cmd.strip().split()

    try:
        dispatch(cmd[0], cmd[1:], session, state, ps)
    except argparse.ArgumentError as e:
        print(f"Command failed! {e}")
    except Exception as e:
        print(e)
