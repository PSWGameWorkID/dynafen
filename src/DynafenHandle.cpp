#include "dynafen.hpp"
#include <cstring>

bool DynafenHandle::get_func(std::string symName, int *index)
{
    for(int i =0 ;i < funcs.size(); i++)
    {
        if(std::strcmp(funcs[0].symName.c_str(), symName.c_str()) == 0)
        {
            *index = i;
            return true;
        }
    }
    *index = -1;
    return false;
}