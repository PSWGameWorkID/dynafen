#if WIN32
#include <windows.h>

void *DynafenCore::load_library(const char *libPath)
{
    return (void*)LoadLibrary(libPath);
}

void *DynafenCore::get_symbol(void *handle, const char *symbol)
{
    return (void*)GetProcAddress((HMODULE)handle, symbol);
}

void DynafenCore::unload_library(void *handle)
{
    FreeLibrary(handle);
}

#endif