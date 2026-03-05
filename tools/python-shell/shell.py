import os
import json
import sys
import importlib
import argparse
import getpass
import traceback

from prompt_toolkit import PromptSession, ANSI
from prompt_toolkit.completion import Completer, Completion
from pathlib import Path

from builder import builder_c


class file_completer_c(Completer):
    def __init__(self, dir):
        self.dir = Path(dir)

    def get_completions(self, doc, c_event):
        text = doc.text_before_cursor.lstrip()
        words = text.split()

        match (len(words) + text.count(' ')):
            case 0:
                # No input yet, complete all commands
                for cmd_file in self.dir.glob("*.py"):
                    cmd_name = cmd_file.stem
                    yield Completion(cmd_name, start_position=0)
            case 1:
                # Completing the top-level command
                last_word = words[-1]

                for cmd_file in self.dir.glob("*.py"):
                    cmd_name = cmd_file.stem
                    if cmd_name.startswith(last_word):
                        yield Completion(
                            cmd_name,
                            start_position=-len(last_word)
                        )
            case _:
                # Completing arguments
                cmd = words[0]
                args = words[1:]
                last_word = args[-1] if args else ""

                try:
                    mod = importlib.import_module(f"commands.{cmd}")
                except ImportError:
                    return
                if not hasattr(mod, "complete"):
                    return
                for flag in mod.complete(last_word):
                    if flag.startswith(last_word):
                        yield Completion(flag, start_position=-len(last_word))


class shell_c:
    wolf_config = Path(".wolfhound", "state.json")
    state: dict

    def __init__(self):
        # Setting up the session
        self.session = {
            "exit": False,
            "home": os.getcwd(),
        }

        self.modules = []
        self.ps = PromptSession()
        self.pc = file_completer_c(dir="tools/python-shell/commands")
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

        self.builder = builder_c(self.session["home"])

    def reload(self):
        for m in list(self.modules):
            sys.modules.pop(m.__name__, None)

        self.modules.clear()
        self.builder = builder_c(self.session["home"])

    def dispatch(self, cmd, args):
        mod = None

        try:
            mod = importlib.import_module(f"commands.{cmd}")

            if mod not in self.modules:
                self.modules.append(mod)

        except ImportError:
            print(f"Unknown command: {cmd}")
            return

        if not hasattr(mod, "execute"):
            print(f"{cmd}: invalid command module")
            return

        mod.execute(self, cmd, args)

    def line(self):
        current_dir = "/".join(os.getcwd().split(os.sep)[-3:]) or "/"

        return ANSI(
            "\n{}@{} --- [ mode : \033[34m{}\033[0m ]\n\033[32mwh-shell>\033[0m ".format(
                self.user,
                current_dir,
                self.builder.display_string(),
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

