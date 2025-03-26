/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GetLib.cpp
*/

#include "GetLib.hpp"
#include "Error.hpp"
#include <dlfcn.h>

void *arcade::utils::load_dll_so(const std::string &name)
{
    void *handle = dlopen(name.c_str(), RTLD_LAZY);

    if (!handle) {
        throw exception::Error("utils::load_dll_so", "Failed to load ", name, " ", dlerror());
    }
    return handle;
}

void arcade::utils::unload_dll_so(void *handle)
{
    if (handle) {
        dlclose(handle);
    }
}
