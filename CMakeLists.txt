cmake_minimum_required(VERSION 3.25.1)
project(Fuse)

# Put binary files on the top level of the build tree for convenience.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# DLLs are runtime for windows.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GenerateExportHeader)
include(${CMAKE_SOURCE_DIR}/cmake/helpers.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Setup conan.
# Currently done in the build script.
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# TODO: Compiler flags

if(WIN32 OR MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_compile_definitions(
        # This sets the minimum feature set to Windows 7.
        _WIN32_WINNT=0x0601
    )
    add_definitions(
        " /Zc:__cplusplus "
        " /std:c++20 "
    )
endif(WIN32 OR MSVC)

if(UNIX AND NOT APPLE)
    add_compile_definitions(

    )
    add_definitions(

    )
endif(UNIX AND NOT APPLE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # -std=c++xx instead of -std=gnu++xx

# Platform agnostic installation trees.
include(GNUInstallDirs)

# This function is used to organize targets for Visual Studio and other IDEs.
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
define_property(
    TARGET
    PROPERTY FOLDER
    INHERITED
    BRIEF_DOCS "Set the folder name."
    FULL_DOCS  "Use to organize targets in an IDE."
)

find_package(CURL REQUIRED)

add_subdirectory_with_folder("utilities" src/utilities/utilities)
add_subdirectory_with_folder("utilities" src/utilities/logger)

add_subdirectory_with_folder("Fuse" src/binaries/fuse)


#enable_testing()
