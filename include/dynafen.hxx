#pragma once

/** Base for dynafen template classes */
class dynafen_base
{
protected:
    /** Exported function pointer */
    void *fn_ptr;

    /** Symbol Name */
    const char *symName;

    /** Library Path */
    const char *libPath;

public:

    /** 
     * Construct a handle and load exported function or increase 
     * the reference in case already loaded
     * @param libPath Path to library ( library handle is cached )
     * @param symName Loaded symbol name
    */
    dynafen_base(const char *libPath, const char *symName);

    /** Destroy the handle, decrease the reference, unload the pointer in
     * in case the reference is 0, unload the entire library in case
     * the no function is disabled */
    ~dynafen_base();

    /** Check if the function pointer is valid, calling invalid
     * function pointer may cause undefined behaviour, but most of
     * the time will make your program crash.
     */
    bool valid();
};

/** 
 * dynamic function loader with return value type of `R`
 * @param R Return type
 * @param Args... The rest of call arguments
 */
template <typename R, typename... Args>
class rdynafen : public dynafen_base
{
public:
    /**
     * Construct a handle and load exported function or increase
     * the reference in case already loaded
     * @param libPath Path to library ( library handle is cached )
     * @param symName Loaded symbol name
     */
    rdynafen(const char* libPath, const char* symName) : dynafen_base(libPath, symName){};

    /**
     * Call the function pointer.
     *
     * For use in case the variable is typeof pointer used by
     * the underlying `operator()(Args ...)`
     *
     * @param args Arguments of the call
     * @return Returned value of the exported function
     */
    R call(Args... args)
    {
        typedef R (*fnSignature)(Args...);
        return ((fnSignature)fn_ptr)(args...);
    }

    /**
     * Call the function pointer.
     *
     * Warning : Check for the validity of the function first before calling
     * @param args Arguments of the call
     * @return Returned value of the exported function
     */
    R operator()(Args... args)
    {
        return this->call(args...);
    }
};

/**
 * dynamic function loader with return value type of `R`
 * @param Args... The rest of call arguments
 */
template <typename... Args>
class vdynafen : public dynafen_base
{
public:
    /**
     * Construct a handle and load exported function or increase
     * the reference in case already loaded
     * @param libPath Path to library ( library handle is cached )
     * @param symName Loaded symbol name
     */
    vdynafen(const char *libPath, const char *symName) : dynafen_base(libPath, symName) {};

    /**
     * Call the function pointer.
     *
     * For use in case the variable is typeof pointer used by
     * the underlying `operator()(Args ...)`
     *
     * @param args Arguments of the call
     */
    void call(Args... args)
    {
        typedef void (*fnSignature)(Args...);
        ((fnSignature)fn_ptr)(args...);
    }

    /**
     * Call the function pointer.
     *
     * Warning : Check for the validity of the function first before calling
     * @param args Arguments of the call
     */
    void operator()(Args... args)
    {
        this->call(args...);
    }
};