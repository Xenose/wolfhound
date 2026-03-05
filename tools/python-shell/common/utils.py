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


def path_complete(dir):
    p = Path(dir)

    if dir.endswith(os.sep):
        parent = p
        prefix = ''
    else:
        if p.parent.exists():
            parent = p.parent
        else:
            parent = Path(".")

        prefix = p.name

    try:
        return [
            str(x) + ('/' if x.is_dir() else '')
            for x in parent.iterdir()
            if x.name.startswith(prefix)
        ]
    except FileNotFoundError:
        return []
