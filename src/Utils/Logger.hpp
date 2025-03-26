/*
** EPITECH PROJECT, 2025
** Game arcade
** File description:
** Logger.hpp
*/

#pragma once

#include "Error.hpp"
#include <iostream>

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
