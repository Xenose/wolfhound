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


def path_complete(dir, only_dir=False):
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
        out = []

        for x in parent.iterdir():
            if x.is_dir():
                out.append(f"{x}/")
            else:
                if only_dir:
                    continue
                out.append(f"{x}")

        return out
    except FileNotFoundError:
        return []
