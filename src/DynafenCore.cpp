#include "dynafen.hpp"
#include <cstring>

DynafenCore *DynafenCore::instance;

void *DynafenCore::load(std::string libPath, std::string symName)
{
    void* handle = nullptr;
    void* fnptr = nullptr;

    // Load Library
    int libIndex = -1;
    if(get_handle(libPath, &libIndex))
    {
        handle = handles[libIndex].handle;
    }
    else
    {
        handle = load_library(libPath);
        if(handle != nullptr)
        {
            DynafenHandle dy {
                .libPath = libPath,
                .handle = handle
            };
            handles.push_back(dy);
            
        }
    }
    
    // Get Symbol
    if (handle != nullptr)
    {
        int fnIndex = -1;
        if (get_handle(libPath, &libIndex) && handles[libIndex].get_func(symName, &fnIndex))
        {
            handles[libIndex].funcs[fnIndex].usages++;
            fnptr = handles[libIndex].funcs[fnIndex].ptr;
        }
        else
        {
            fnptr = get_symbol(handle, symName);
            if(fnptr != nullptr)
            {
                handles[libIndex].funcs.push_back(DynafenFuncs{
                    .symName = symName,
                    .ptr = fnptr,
                    .usages = 1
                });
            }
        }
    }

    cleanup();
    return fnptr;
}

void DynafenCore::unload(std::string libPath, std::string symName)
{
    int libIndex = -1;
    if(get_handle(libPath, &libIndex))
    {
        DynafenHandle* handle = &handles[libIndex];
        int fnIndex;
        if (handle->get_func(symName, &fnIndex))
        {
            handle->funcs[fnIndex].usages--;

            // Function is no longer needed, removing
            if(handle->funcs[fnIndex].usages <= 0)
            {
                handle->funcs.erase(handle->funcs.begin() + fnIndex);
            }
        }

        // No function is needed, cleaning up
        if (handle->funcs.size() == 0)
        {
            unload_library(handle->handle);
            handles.erase(handles.begin() + libIndex);
        }
    }
    cleanup();
}

void DynafenCore::cleanup()
{
    std::vector<std::string> remove_handle;
    for (auto handle : handles)
    {
        std::vector<std::string> remove_funcs;
        for (auto fn : handle.funcs)
        {
            if (fn.usages < 0)
            {
                remove_funcs.push_back(fn.symName);
            }
        }

        // Clear handles
        for (std::string name : remove_funcs)
        {
            int at = -1;
            if (handle.get_func(name, &at)){
                handle.funcs.erase(handle.funcs.begin() + at);
            }                
        }

        if (handle.funcs.size() == 0)
        {
            unload_library(handle.handle);
            remove_handle.push_back(handle.libPath);
        }
    }

    for (std::string name : remove_handle)
    {
        int libIndex = -1;
        if(get_handle(name, &libIndex))
        {
            handles.erase(handles.begin() + libIndex);
        }
    }
}

bool DynafenCore::get_handle(std::string libPath, int *index)
{
    for (int i = 0; i < handles.size(); i++)
    {
        if (std::strcmp(handles[i].libPath.c_str(), libPath.c_str()) == 0)
        {
            *index = i;
            return true;
        }
    }
    *index = -1;
    return false;
}