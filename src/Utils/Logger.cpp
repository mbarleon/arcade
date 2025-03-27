/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Logger.cpp
*/

#include "Logger.hpp"
#include <iostream>

/**
 * @file Logger.cpp
 * @brief This file contains functions for writing debug logs.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * Debug logs are tools intended for developers.
 * They are not meant for the end user, but rather to assist in diagnosing
 * and fixing potential errors during development.
 */

/**
 * @brief Writes a log message.
 * @details Outputs a log message to the terminal to assist the developer during the debugging process.
 * @return void
 */
void arcade::logger::error(const arcade::exception::Error &e)
{
    std::cerr << RED_BOLD << "╔════════════════════════════════╗" << RESET << std::endl;
    std::cerr << RED_BOLD << "║       ⚠ ERROR OCCURRED ⚠       ║" << RESET << std::endl;
    std::cerr << RED_BOLD << "╚════════════════════════════════╝" << RESET << std::endl;

    std::cerr << YELLOW << "⮞ Raised by: " << RESET << e.where() << std::endl;
    std::cerr << YELLOW << "⮞ Reason:    " << RESET << e.what() << std::endl;
}
