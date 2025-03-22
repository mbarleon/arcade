/*
** EPITECH PROJECT, 2025
** B-OOP-400-STG-4-1-arcade-mathieu.barleon
** File description:
** Utils
*/

#pragma once

#include <cstdint>

namespace arcade::utils {
    enum components_e { R, G, B, A };

    typedef union color_u {
        uint32_t color;
        uint8_t components[4];
    } color_t;
};
