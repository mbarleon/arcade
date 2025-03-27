/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** main
*/

#include <cstring>
#include <iostream>
#include "../Core/Core.hpp"
#include "../Utils/Error.hpp"
#include "../Utils/Logger.hpp"

/**
 * @file main.cpp
 * @brief Main entry point of the program.
 * @author mbarleon
 * @version 1.0
 * @date 2025-03-26
 *
 * @details
 * This file contains the main() function. It handles basic launch errors and triggers
 * the execution of the main game loop.
 */

/**
 * @brief Displays the help message.
 * @details This message summarizes the correct usage of the program.
 * It can be displayed after an error or upon explicit request (e.g., with the '-h' option).
 */
static void helper(void)
{
    std::cout << "ARCADE" << std::endl;
    std::cout << "\t[DESCRIPTION]:" << std::endl;
    std::cout << "\t\tArcade games where you can launch multiple games in multiple graphic libraries." << std::endl;
    std::cout << "\t[USAGE]:" << std::endl;
    std::cout << "\tarcade [graphic_library]" << std::endl;
}

/**
 * @brief Checks whether the program execution should be interrupted.
 * @details Handles simple error cases such as an incorrect number of arguments or help request (using the '-h' option).
 * @return The path to the graphical library to be loaded, if no interruption is detected.
 */
static const char *error_handling(int ac, char **av)
{
    if (ac != 2)
        throw arcade::exception::Error("error_handling", "Wrong number of arguments");
    if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0) {
        helper();
        exit(0);
    }
    return av[1];
}

/**
 * @brief Main function.
 * @details Catches errors and displays them. If no error is detected, the program runs normally.
 * @return 0 on success, 84 on error.
 */
int main(int ac, char **av)
{
    const char *display;
    arcade::core::Core core;

    try {
        display = error_handling(ac, av);
        core.run(display);
    } catch (arcade::exception::Error &e) {
        arcade::logger::error(e);
        return 84;
    }
    return 0;
}
