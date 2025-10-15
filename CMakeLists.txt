cmake_minimum_required(VERSION 3.31)

set(CMAKE_VER_FULL "${CMAKE_VERSION}")
file(READ "${CMAKE_CURRENT_LIST_DIR}/cmake_import_std_uuids.json" _json_str)
string(REGEX MATCH "\"${CMAKE_VER_FULL}\"[ \t]*:[ \t]*\"([0-9a-fA-F\\-]+)\"" _match "${_json_str}")

if(_match)
    string(REGEX REPLACE ".*\"${CMAKE_VER_FULL}\"[ \t]*:[ \t]*\"([0-9a-fA-F\\-]+)\".*" "\\1" _uuid "${_match}")
    message(STATUS "Detected CMake version ${CMAKE_VER_FULL}, using import_std UUID = ${_uuid}")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "${_uuid}")
else()
    message(WARNING "No UUID found for CMake version ${CMAKE_VER_FULL} in cmake_import_std_uuids.json — import std will be disabled")
endif()

project(test_cpp23_import_std LANGUAGES CXX)
if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(FATAL_ERROR
                "Detected the use of MinGW GCC compiler on Windows.\n"
                "MinGW GCC has serious compatibility issues with C++23 modules (import std).\n"
                "Please switch to Clang (such as llvm-mingw) or MSVC for compilation."
        )
    endif()
endif()

set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_cpp23_import_std main.cpp)
