#include "dynafen.hpp"

dynafen_base::dynafen_base(const char *libPath, const char *symName) : libPath(libPath), symName(symName)
{
    if(DynafenCore::instance == nullptr) DynafenCore::instance = new DynafenCore();

    fn_ptr = DynafenCore::instance->load(std::string(libPath), std::string(symName));
}

dynafen_base::~dynafen_base()
{
    if(DynafenCore::instance == nullptr) DynafenCore::instance = new DynafenCore();
    DynafenCore::instance->unload(std::string(libPath), std::string(symName));
    symName = libPath = nullptr;
    fn_ptr = nullptr;
}

bool dynafen_base::valid()
{
    return fn_ptr != nullptr;
}
