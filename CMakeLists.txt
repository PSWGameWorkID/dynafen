cmake_minimum_required(VERSION 3.10)

project(dynafen VERSION 1.0.0.0)
include(GNUInstallDirs)

set(dynafen_src "src/DynafenBase.cpp" "src/DynafenCore.cpp" "src/DynafenHandle.cpp")

if(LINUX)
    list(APPEND dynafen_src "src/DynafenCore.Linux.cpp")
elseif(WIN32)
    list(APPEND dynafen_src "src/DynafenCore.Win32.cpp")
endif()

add_library(dynafen STATIC ${dynafen_src})
target_include_directories(dynafen PUBLIC "include")

if(LINUX)
    target_link_directories(dynafen PRIVATE dl)
elseif(WIN32)
    target_link_directories(dynafen PRIVATE kernel32)
endif()

option(BUILD_TEST "Build test apps" ON)

if(BUILD_TEST)
    add_executable(testbin "test/test_compile.cpp")
    add_library(testlib SHARED "test/test_lib.cpp")
    target_link_libraries(testbin PRIVATE dynafen)

    add_test(NAME "Dynafen Main Test" COMMAND $<TARGET_FILE:testbin>)
endif()

install(DIRECTORY include DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/.."
    FILES_MATCHING PATTERN dynafen.hxx)

install(TARGETS dynafen
    EXPORT dynafenTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Pack)