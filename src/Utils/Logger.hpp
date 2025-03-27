/*
** EPITECH PROJECT, 2025
** Game arcade
** File description:
** Logger.hpp
*/

#pragma once

#include "Error.hpp"
#include <iostream>

/**
 * @file Logger.hpp
 * @brief This file contains the class used for writing debug logs.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * Debug logs are tools intended for developers.
 * They are not meant for the end user, but are used to assist in diagnosing
 * and fixing potential errors during development.
 */

namespace arcade::logger {
    constexpr const char *GRAY = "\033[38;5;8m";
    constexpr const char *RED_BOLD = "\033[1;31m";
    constexpr const char *YELLOW = "\033[1;33m";
    constexpr const char *RESET = "\033[0m";

    void error(const arcade::exception::Error &e);

    template<typename... Args>
    void debug(Args &&...args)
    {
        std::ostringstream oss;
        int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
        std::cout << YELLOW << "[DEBUG] " << RESET << oss.str() << std::endl;
    }
};// namespace arcade::logger
