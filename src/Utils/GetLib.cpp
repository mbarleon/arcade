/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GetLib.cpp
*/

#include "GetLib.hpp"
#include "Error.hpp"
#include <dlfcn.h>

/**
 * @file GetLib.cpp
 * @brief This file handles loading and unloading of graphical libraries.
 * @author Shared with the partner group
 * @version 1.0
 * @date 2025-03-26
 *
 * @details This file contains all functions that dynamically open and close shared libraries (*.so)
 * using dlopen and dlclose. Custom exceptions are thrown in case of errors.
 */

/**
 * @brief Loads a shared library (.so).
 * @details This function dynamically loads a shared library (.so) using dlopen,
 * in order to access the graphical functions required for the Arcade and the current game to work properly.
 * @return A handle (void*) that can be passed to dlsym to retrieve symbols from the library.
 */
void *arcade::utils::load_dll_so(const std::string &name)
{
    void *handle = dlopen(name.c_str(), RTLD_LAZY);

    if (!handle) {
        throw exception::Error("utils::load_dll_so", "Failed to load ", name, " ", dlerror());
    }
    return handle;
}

/**
 * @brief Unloads a shared library (.so).
 * @details This function closes a shared library (.so) using dlclose when it is no longer needed.
 * @return void
 */
void arcade::utils::unload_dll_so(void *handle)
{
    if (handle) {
        dlclose(handle);
    }
}
