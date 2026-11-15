import os
import shutil
import subprocess
import tempfile

try:
    import git

    _IMPORTED_GIT=True
except ImportError:
    _IMPORTED_GIT=False

from common.params import params_c


prompt = "Write a short detailed commit summary for the changes below. No prefixes like chore/feat, no echoing instructions, strictly the summary:"
model_path = os.path.expanduser("~/.cache/models/qwen2.5-coder-3b-instruct-q4_k_m.gguf")


def confirm(text="Are you sure?"):
    while True:
        # i for input
        i = input(f"{text} [yes/no]: ").strip().lower()

        if "yes" == i:
            return True
        elif "no" == i:
            return False


def execute(params: params_c):
    summary = ""

    if not _IMPORTED_GIT:
        print("Failed to pull in python git!")
        return

    if not shutil.which("llama-cli"):
        print("llama-cli not installed!")
        return

    repo = git.Repo(params.sh.session["home"])

    # The prompt to feed the LLM
    git_diff = repo.git.diff("HEAD~1", "HEAD", unified=10)
    full_promt = f"{prompt}\n\n{git_diff}"

    with tempfile.NamedTemporaryFile(mode="w", delete=False, suffix=".txt") as tmp_out:
        tmp_out_path = tmp_out.name

    try:
        subprocess.run([
            "llama-cli",
            "-m", model_path,
            "-p", full_promt,
            "-o", tmp_out_path,
            "-c", str(8096),
            "-n", str(8096),
            "-st", 
            "-t", str(20),
            "--temp", str(0.2),
        ], check=True, text=True)

        if os.path.exists(tmp_out_path):
            with open(tmp_out_path, "r", encoding="utf-8") as f:
                summary = f.read().strip()
                summary = summary[summary.rfind("Assistant:") + 11:]

    finally:
        if os.path.exists(tmp_out_path):
            os.remove(tmp_out_path)

    print(f"\n-----\n{summary}\n-----\n")

    if confirm("Use message for commit?"):
        pass
