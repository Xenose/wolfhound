import sys
import shutil
import platform
import subprocess


def clipboard_copy(text):
    program = None
    plat = sys.platform.lower()

    match plat:
        case "win32":
            program = "clip"
        case "darwin":
            program = "pbcopy"
        case "android":
            if shutil.which("termux-clipboard-set"):
                program = "termux-clipboard-set"
        case _ if plat.startswith(("linux", "freebsd", "sunos")):
            # Checking for WSL
            if "microsoft" in platform.uname().release.lower():
                program = "clip.exe"
            elif shutil.which("wl-copy"):
                program = "wl-copy"
            elif shutil.which("xclip"):
                program = "xclip"
        # end match

    if program is None:
        return "No clipboard program found!"

    p = subprocess.Popen(
        [program],
        stdin=subprocess.PIPE,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL
    )

    p.communicate(text.encode("utf-8"))
    return "Copied to clipboard!"


def clipboard_paste():
    pass
