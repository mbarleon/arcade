##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## open
##

#!/bin/bash

if [ $(uname -s) == 'Darwin' ]; then
    open ./doc/html/index.html
else
    xdg-open ./doc/html/index.html
fi
