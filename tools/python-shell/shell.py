import os
import json
import importlib
import argparse
import getpass
import traceback

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


class shell_c:
    wolf_config = Path(".wolfhound", "state.json")
    state: {}

    def __init__(self):
        # Setting up the session
        self.session = {
            "exit": False,
            "home": os.getcwd(),
        }

        self.ps = PromptSession()
        self.pc = file_completer_c(dir="tools/python-shell/bin")
        self.dispatch("clear", None)
        self.dispatch("welcome", None)
        self.user = getpass.getuser()

        if os.path.exists(".wolfhound/state.json"):
            print("State found")
            with open(".wolfhound/state.json", "r") as fd:
                self.state = json.loads(fd.read())
        else:
            print("No state found creating one")
            self.state = {}

    def dispatch(self, cmd, args):
        mod = None

        try:
            mod = importlib.import_module(f"bin.{cmd}")
        except ImportError:
            print(f"Unknown commnad: {cmd}")
            return

        if not hasattr(mod, "execute"):
            print(f"{cmd}: invalid command module")
            return

        mod.execute(self, cmd, args)

    def line(self):
        current_dir = "/".join(os.getcwd().split(os.sep)[-3:]) or "/"

        return ANSI(
            "\n{}@{}\n\033[32mwh-shell>\033[0m ".format(
                self.user,
                current_dir
            )
        )

    def start(self):
        while not self.session["exit"]:
            cmd = self.ps.prompt(
                self.line(),
                completer=self.pc
            )

            if not cmd:
                continue

            cmd = cmd.strip().split()

            try:
                self.dispatch(cmd[0], cmd[1:])
            except argparse.ArgumentError as e:
                print(f"Command failed! {e}")
            except Exception as e:
                error_text = traceback.format_exc()
                print(f"command failed {e} :: {error_text}")

