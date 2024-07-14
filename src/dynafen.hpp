#pragma once
#include <dynafen.hxx>
#include <map>
#include <vector>
#include <string>

struct DynafenFuncs
{
    std::string symName;
    void *ptr;
    int usages;
};

struct DynafenHandle
{
    std::string libPath;
    void *handle;
    std::vector<DynafenFuncs> funcs = std::vector<DynafenFuncs>();
    bool get_func(std::string symName, int *index);
};

class DynafenCore
{
private:
    std::vector<DynafenHandle> handles = std::vector<DynafenHandle>();
    void *load(std::string lib, std::string sym);
    void unload(std::string lib, std::string sym);
    void cleanup();

    bool get_handle(std::string libName, int* index);

    void *load_library(std::string libPath);
    void *get_symbol(void *handle, std::string symbol);
    void  unload_library(void* handle);
    static DynafenCore* instance;

    friend dynafen_base;
};
