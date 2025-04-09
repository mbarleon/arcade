##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## ReadFlags
##

def readFlags(ldflags: str, default_value: str) -> list[str]:
    ret = ldflags.split(':')
    for v in ret:
        if v.startswith('-'):
            raise ValueError
    if (default_value is not None):
        ret.insert(0, default_value)
    return ret
