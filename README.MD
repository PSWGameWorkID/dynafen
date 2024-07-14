# Dynafen
C++11 template-based dynamic library function loader. 

Originally made for a personal experimentation and coding practice.

> [!WARNING]
> So far only supports dynamic library that is compiled from C code or 
> C++ code that is using `extern "C"`, as only code demangling that is
> available during runtime, but not code mangling.

## Features
- Cross-platform
- Library handle is reference counted
  > Meaning a loaded library will be unloaded if no function in it is no longer needed.
- Simple function construction.
- Simple pointer validity check
- Call imported function like a normal C++ function
- Good for IDE autocompletion support

## Building and Installation
### Requirements
- CMake 3.10 or later
- C++ Compiler with C++11 variadic template support
    - LLVM clang 2.9 or later
    - GNU gcc 4.4 or later
    - MSVC 18.0 (Visual Studio 2013) or later
- Build system like Ninja, GNU Make or MSBuild

### Steps
```bash
# Clone the repository
git clone https://github.com/PSWGameWorkID/dynafen
cd dynafen

# Build the project ( You can change Ninja to other build system too )
mkdir build
cd build
cmake -B . -S .. -G Ninja -DCMAKE_BUILD_TYPE=MinSizeRel
ninja

# Install as system library ( Linux only )
sudo cmake --install .
```

### Prebuilt 
The Release page only have package for x86-64 Linux build with GCC and Clang.

## Exported Functions
### `#include <dynafen.hxx>`
- `vdynafen<Args...>::vdynafen(const char* libPath, const char* symName)`
  
    Construct and load an exported function with void return type named `symName` from dynamic library at `libPath`
- `void vdynafen<Args..>::operator(Args ...)`
    
    Call the exported function
- `rdynafen<R, Args...>::rdynafen(const char* libPath, const char* symName)`
    
    Construct and load an exported function with `R` return type named `symName` from dynamic library at `libPath`
- `R vdynafen<R, Args..>::operator(Args ...)`
    
    Call the exported function
- `bool dynafen_base::valid()`
    
    Check if the pointer is valid, calling invalid pointer may cause undefined behaviour, but mostly crash your app.
    This call is available for both function classes since `dynafen_base` is it's base class.

## Adding to your Program
```bash
# Using installed library
gcc -o yourprogram -ldynafen "main.cpp"

# Using built library, but not installed
gcc -o yourprogram -I/path/to/lib/dynafen/ -L/path/to/lib/dynafen/build -ldynafen "main.cpp"
```

## Example
```cpp
#include <dynafen.hxx>

...
const char* const library1 = "./lib/libmy.1.so";
const char* const mathlib = "./s";
vdynafen<> my_void_function(library1, "my_void_function"); // equals to `void my_void_function(void)`

vdynafen<int> my_void_int_function(library1, "my_void_int_function"); // equals to `void my_void_int_function(int arg1)`

rdynafen<int, int, int> my_multiply(mathlib, "my_multiply"); // equals to `int my_multiply(int, int)`

rdynafen<int> my_getter(library1, "my_getter"); // equals to `int my_getter(void)`
...

// Call like a C++ function
my_void_function();
my_void_int_function(100);
int s = my_multiply(10, 10);
int data = my_getter();

// Check if this function valid
if(my_getter.valid())
{
    int val = my_getter();
}
```

## Dependencies
Only C++11 Standard Library and platform-specific dynamic loader.

## See Also
- [martin-olivier/dylib](https://github.com/martin-olivier/dylib) project
  
  More featured, more OOP-based approach, overall a better library.

## License
MIT License ( See [LICENSE](LICENSE) )
