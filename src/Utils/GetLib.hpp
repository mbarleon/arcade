/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GetLib.hpp
*/

#pragma once

#include "Error.hpp"
#include <dlfcn.h>
#include <string>

namespace arcade::utils {
    template<typename T>
    T getFunction(const std::string &name, void *handle);
    void *load_dll_so(const std::string &name);
    void unload_dll_so(void *handle);
};// namespace arcade::utils
