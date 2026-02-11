import subprocess


def execute(cmd, args, session, state, prompt):
    subprocess.run(args, check=False)
