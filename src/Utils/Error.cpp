/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Core.cpp
*/

#include "Error.hpp"

/**
 * @file Error.cpp
 * @brief Functions used by the program's custom exception class.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file contains all the functions used by the custom exception class created for the Arcade project,
 * which inherits from the standard std::exception class.
 */

/**
 * @brief Retrieves the position of the error.
 * @details This function returns information about the location of the error (such as file and line number),
 * to help with debugging.
 * @return A string indicating the origin of the error (file and line).
 */
const char *arcade::exception::Error::where(void) const noexcept
{
    return _where.c_str();
}

/**
 * @brief Provides an explanation of the encountered error.
 * @details This function returns a detailed error message, which is retrieved by the main() function
 * and displayed to the user to help understand the issues detected by the program.
 * @return A string containing the error message.
 */
const char *arcade::exception::Error::what(void) const noexcept
{
    return _what.c_str();
}
