##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Main
##

import os
from typing import Literal
from sys import exit, stderr
from .ReadFlags import readFlags
from .ParseArgs import parseArgs
from .BuildFiles import buildFiles

def getTarget(mode: Literal["game", "graphical", "menu"]):
    if (mode == "graphical"):
        return "Graphicals"
    else:
        return "Games"

def getFiles(mode: Literal["game", "graphical", "menu"]):
    if (mode == "game"):
        return "Games"
    elif (mode == "graphical"):
        return "Graphicals"
    else:
        return "Menu"

def main(argv: list[str]):
    current_file_path = os.path.abspath(__file__)
    current_dir = os.path.dirname(current_file_path)
    os.chdir(current_dir)

    mode, name, force, ldflags, ldlibs = parseArgs(argv)
    targetFolder = os.path.join("..", "..", "src", getTarget(mode))
    files = getFiles(mode)

    try:
        if (ldflags is not None):
            ldflags = readFlags(ldflags, "$(UTILS)")
        if (ldlibs is not None):
            ldlibs = readFlags(ldlibs, "arcade_utils")
    except ValueError:
        print("Error in ldlibs or ldflags.", file=stderr)
        exit(84)

    try:
        buildFiles(targetFolder, files, name, force, ldflags, ldlibs)
    except FileExistsError:
        print("Error: folder already exists and force was not specified.", file=stderr)
        exit(84)
    except OSError:
        print("FATAL ERROR: ABORTING", file=stderr)
        exit(84)
