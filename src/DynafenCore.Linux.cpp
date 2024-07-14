#include "dynafen.hpp"
#include <dlfcn.h>

#ifndef DYNAFEN_RTLD_MODE_LINUX
#define DYNAFEN_RTLD_MODE_LINUX RTLD_LAZY
#endif

void *DynafenCore::load_library(std::string libPath)
{
    return dlopen(libPath.c_str(), DYNAFEN_RTLD_MODE_LINUX);
}

void *DynafenCore::get_symbol(void *handle, std::string symbol)
{
    return dlsym(handle, symbol.c_str());
}

void DynafenCore::unload_library(void *handle)
{
    dlclose(handle);
}