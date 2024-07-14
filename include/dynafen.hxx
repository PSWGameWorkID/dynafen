#pragma once

class dynafen_base
{
protected:
    void *fn_ptr;
    const char *symName;
    const char *libPath;

public:
    dynafen_base(const char *libPath, const char *symName);
    ~dynafen_base();

    bool valid();
};

template <typename R, typename... Args>
class rdynafen : public dynafen_base
{
public:
    rdynafen(const char* libPath, const char* symName) : dynafen_base(libPath, symName){};
    R call(Args... args)
    {
        typedef R (*fnSignature)(Args...);
        return ((fnSignature)fn_ptr)(args...);
    }

    R operator()(Args... args)
    {
        return this->call(args...);
    }
};

template <typename... Args>
class vdynafen : public dynafen_base
{
public:
    vdynafen(const char *libPath, const char *symName) : dynafen_base(libPath, symName) {};
    void call(Args... args)
    {
        typedef void (*fnSignature)(Args...);
        ((fnSignature)fn_ptr)(args...);
    }

    void operator()(Args... args)
    {
        this->call(args...);
    }
};