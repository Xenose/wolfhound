import os

from pathlib import Path


def find_executable(dir: Path, exclude: [] = []):
    out = []

    for f in os.scandir(dir):
        if f.name in exclude:
            continue

        if f.is_dir(follow_symlinks=False):
            out.extend(find_executable(Path(f.path), exclude))
        elif os.access(f.path, os.X_OK):
            out.append(f.path)

    return out
