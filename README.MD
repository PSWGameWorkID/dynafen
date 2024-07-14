# Dynafen
C++11 template-based dynamic library function loader. 

> [!WARNING]
> So far only supports dynamic library that is compiled from C code or 
> C++ code that is using `extern "C"`, as only code demangling that is
> available during runtime, but not code mangling.

## Building and Installation
### Requirements
- CMake 3.10 or later
- C++ Compiler with C++11 variadic template support
    - LLVM clang 2.9
    - GNU gcc 4.4
    - MSVC 18.0
- Build system like Ninja, GNU Make or MSBuild

### Steps
```bash
# Clone the repository
git clone https://github.com/PSWGameWorkID/dynafen
cd dynafen

# Build the project ( You can change Ninja to other build system too )
mkdir build
cd build
cmake -B . -S .. -G Ninja
ninja

# Install as system library ( Linux only )
sudo cmake --install .

```

## Exported Functions
### `#include <dynafen.hxx>`
- `vdynafen<Args...>::vdynafen(const char* libPath, const char* symName)`
    > Construct and load an exported function with void return type named `symName` from dynamic library at `libPath`
- `void vdynafen<Args..>::operator(Args ...)`
    > Call the exported function
- `rdynafen<R, Args...>::rdynafen(const char* libPath, const char* symName)`
    > Construct and load an exported function with `R` return type named `symName` from dynamic library at `libPath`
- `R vdynafen<R, Args..>::operator(Args ...)`
    > Call the exported function
- `bool dynafen_base::valid()`
    > Check if the pointer is valid, calling invalid pointer may cause undefined behaviour, but mostly crash your app.
    > This call is available for both function classes since `dynafen_base` is it's base class.

## Example
```cpp
#include <dynafen.hxx>

...
const char* const library1 = "./lib/libmy.1.so";
const char* const mathlib = "./s";
vdynafen my_void_function(library1, "my_void_function"); // equals to `void my_void_function(void)`

vdynafen<int> my_void_int_function(library1, "my_void_int_function"); // equals to `void my_void_int_function(int arg1)`

rdynafen<int, int, int> my_multiply(mathlib, "my_multiply"); // equals to `int my_multiply(int, int)`

rdynafen<int> my_getter(library1, "my_setter"); // equals to `int my_getter(void)`
...

// Check if this function valid
if(my_getter.valid())
{
    int val = my_getter();
}
```

## Dependencies
Only C++11 Standard Library and platform-specific dynamic loader.

## License
MIT License ( See [LICENSE](LICENSE) )
