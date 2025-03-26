/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** main
*/

#include <iostream>
#include "../Core/Core.hpp"
#include "../Utils/Error.hpp"

static void helper(void)
{
    std::cout << "ARCADE" << std::endl;
    std::cout << "\t[DESCRIPTION]:" << std::endl;
    std::cout << "\t\tArcade games where you can launch multiple games in multiple graphic libraries." << std::endl;
    std::cout << "\t[USAGE]:" << std::endl;
    std::cout << "\tarcade [graphic_library]" << std::endl;
}

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

int main(int ac, char **av)
{
    const char *display;

    try {
        display = error_handling(ac, av);
        arcade::core::Core().run(display);
    } catch (arcade::exception::Error &e) {
        std::cerr << "ERROR: " << e.what() << " at " << e.where() << std::endl;
        return 84;
    }
    return 0;
}
