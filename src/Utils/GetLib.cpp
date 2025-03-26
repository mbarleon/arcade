/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** GetLib.cpp
*/

#include "GetLib.hpp"
#include "Error.hpp"
#include <dlfcn.h>

template<typename T>
T arcade::utils::getFunction(const std::string &name, void *handle)
{
    dlerror();

    T func = reinterpret_cast<T>(dlsym(handle, name.c_str()));
    const char *error = dlerror();

    if (error) {
        throw exception::Error("utils::getFunction", "failed to find function: ", name, " ", error);
    }
    return func;
}

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
