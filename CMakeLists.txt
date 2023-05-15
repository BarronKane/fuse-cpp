cmake_minimum_required(VERSION 3.25.1)
project(Fuse)

include(GenerateExportHeader)
include(${CMAKE_SOURCE_DIR}/cmake/helpers.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Setup conan.
# Currently done in the build script.
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# TODO: Compiler flags

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_compile_definitions(
        _WIN32_WINNT=0x0601
    )
endif(WIN32)

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

add_subdirectory_with_folder("Fuse" src/binaries/fuse)

add_subdirectory_with_folder("utilities" src/utilities/logger)


#enable_testing()
