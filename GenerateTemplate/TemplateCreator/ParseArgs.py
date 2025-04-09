##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## ParseArgs
##

from typing import TextIO
from sys import exit, stdout, stderr
from getopt import getopt, GetoptError

def helper(file: TextIO=stdout) -> None:
    print("""    Usage: python3 templateCreator.py [OPTIONS]

    Supported options:
        -h, --help                                          Show help message
        -m, --mode=[game|graphical|menu]                    Set the mode (expects a value, mandatory)
        -n, --name=                                         Set the name (expects a value, mandatory)
        -f, --force                                         Force operation (flag, optional)
        -d, --ldflags=[flags separated by semicolons]       Set linker flags separated by commas (expects a value, optional)
        -l, --ldlibs=[libraries separated by semicolons]    Set linker libraries separated by commas (expects a value, optional)""", file=file)

def parseArgs(argv: list[str]) -> tuple[str, str, bool, str, str]:
    mode = name = force = ldflags = ldlibs = None

    try:
        opts, args = getopt(argv, "hm:n:fd:l:", ["help", "mode=", "name=", "force", "ldflags=", "ldlibs="])
    except GetoptError:
        helper(stderr)
        exit(84)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            helper()
            exit(0)
        elif opt in ("-m", "--mode"):
            mode = arg
        elif opt in ("-n", "--name"):
            name = arg
        elif opt in ("-f", "--force"):
            force = True
        elif opt in ("-d", "--ldflags"):
            ldflags = arg
        elif opt in ("-l", "--ldlibs"):
            ldlibs = arg
        else:
            helper(stderr)
            exit(84)

    if (mode == "menu" and name == None):
        name = "menu"

    if None in (mode, name) or (mode not in ("game", "graphical", "menu")):
        helper(stderr)
        exit(84)

    if (mode == "menu" and name.lower() != "menu"):
        print("Menu's name must be \"menu\". User input will be ignored.", file=stderr)
        name = "menu"

    return mode, name, False if force is None else True, ldflags, ldlibs
