##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## buildFiles
##

from os.path import exists, join
from os import remove, mkdir, listdir

def getNewName(file: str, name: str) -> str:
    new_filename = (
        file
        .replace("__Name__", name.capitalize())
        .replace("__NAME__", name.upper())
        .replace("__name__", name.lower())
    )
    return new_filename

def getString(strlist: list[str], flag: str) -> str:
    return " ".join(f"{flag}{ld}" for ld in strlist)

def applyReplacements(content: str, name: str, ldflags: list[str], ldlibs: list[str]) -> str:
    new_content = (
        content
        .replace("__Name__", name.capitalize())
        .replace("__NAME__", name.upper())
        .replace("__name__", name.lower())
        .replace("__ldflags__", getString(ldflags, "-L"))
        .replace("__ldlibs__", getString(ldlibs, "-l"))
    )
    return new_content

def processFile(targetFolder: str, files: str, file: str, name: str, ldflags: list[str], ldlibs: list[str]) -> None:
    with open(join(files, file), "r") as f:
        content = f.read()

    newContent = applyReplacements(content, name, ldflags, ldlibs)
    newFile = getNewName(file, name)

    if (newContent is None):
        remove(targetFolder)
        raise OSError
    with open(join(targetFolder, newFile), "w") as f:
        f.write(newContent)

def buildFiles(targetFolder: str, files: str, name: str, force: bool, ldflags: list[str], ldlibs: list[str]) -> None:
    if exists(targetFolder):
        if (force == True):
            remove(targetFolder)
        else:
            raise FileExistsError

    mkdir(targetFolder)
    for file in listdir(files):
        processFile(targetFolder, files, file, name, ldflags, ldlibs)
