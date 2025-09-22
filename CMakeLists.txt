cmake_minimum_required(VERSION 4.0.3)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
project(test_cpp23_import_std LANGUAGES CXX)
set(CMAKE_CXX_MODULE_STD 1)
set(CMAKE_CXX_STANDARD 23)

add_executable(test_cpp23_import_std main.cpp)
