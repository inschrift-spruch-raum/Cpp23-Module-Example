cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(C++23-Module-Example LANGUAGES CXX)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(MSYS2_Clang "Compile using Clang in MSYS2" OFF)

# find Vulkan SDK
find_package( Vulkan REQUIRED )

# Require Vulkan version ≥ 1.3.256 (earliest version when the Vulkan module was available)
if( ${Vulkan_VERSION} VERSION_LESS "1.3.256" )
  message( FATAL_ERROR "Minimum required Vulkan version for C++ modules is 1.3.256. "
           "Found ${Vulkan_VERSION}."
  )
endif()

# set up Vulkan C++ module as a library
add_library( VulkanHppModule )
target_sources( VulkanHppModule PUBLIC
  FILE_SET CXX_MODULES
  BASE_DIRS ${Vulkan_INCLUDE_DIR}
  FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm
  FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan_video.cppm
)
target_compile_features( VulkanHppModule PUBLIC cxx_std_23 )
target_compile_definitions( VulkanHppModule
    PRIVATE
    VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_USE_STD_EXPECTED
    VULKAN_HPP_NO_SMART_HANDLE
    VULKAN_HPP_NO_CONSTRUCTORS
)
target_link_libraries( VulkanHppModule PUBLIC Vulkan::Headers )

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/utf-8>)

# link Vulkan C++ module into your project
add_executable(C++23-Module-Example src/main.cpp)
target_link_libraries( C++23-Module-Example PRIVATE VulkanHppModule )

if(MSYS2_Clang)
    target_link_libraries(C++23-Module-Example PRIVATE 
        -static
    )
endif()
