/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Logger.cpp
*/

#include "Logger.hpp"
#include <iostream>

void arcade::logger::error(const arcade::exception::Error &e)
{
    std::cerr << RED_BOLD << "╔════════════════════════════════╗" << RESET << std::endl;
    std::cerr << RED_BOLD << "║       ⚠ ERROR OCCURRED ⚠       ║" << RESET << std::endl;
    std::cerr << RED_BOLD << "╚════════════════════════════════╝" << RESET << std::endl;

    std::cerr << YELLOW << "⮞ Raised by: " << RESET << e.where() << std::endl;
    std::cerr << YELLOW << "⮞ Reason:    " << RESET << e.what() << std::endl;
}
