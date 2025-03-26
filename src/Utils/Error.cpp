/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core.cpp
*/

#include "Error.hpp"

/*
* public
*/

/*
 * INFO:
 * this allows you to get where the error happened
 */
const char *arcade::exception::Error::where(void) const noexcept
{
    return _where.c_str();
}

/*
 * INFO:
 * this allows you to get the error message
 */
const char *arcade::exception::Error::what(void) const noexcept
{
    return _what.c_str();
}
