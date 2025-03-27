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

/**
 * @file GetLib.cpp
 * @brief This file contains the function responsible for managing shared libraries (.so).
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details The fucntion allow loading, unloading, and extracting symbols from .so files,
 * in order to dynamically use game and graphical libraries using dlopen, dlclose, and dlsym.
 */

namespace arcade::utils {
    template<typename T>
    T getFunction(const std::string &name, void *handle)
    {
        dlerror();

        T func = reinterpret_cast<T>(dlsym(handle, name.c_str()));
        const char *error = dlerror();

        if (error) {
            throw exception::Error("utils::getFunction", "failed to find function: ", name, " ", error);
        }
        return func;
    }
    void *load_dll_so(const std::string &name);
    void unload_dll_so(void *handle);
};// namespace arcade::utils
