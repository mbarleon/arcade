/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Error
*/

#include "Error.hpp"

const char *arcade::error::Error::where(void) const noexcept
{
    return _where.c_str();
}

const char *arcade::error::Error::what(void) const noexcept
{
    return _what.c_str();
}
