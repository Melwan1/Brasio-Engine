######################################################################
#    ____                _         _____             _               #
#   | __ ) _ __ __ _ ___(_) ___   | ____|_ __   __ _(_)_ __   ___    #
#   |  _ \| '__/ _` / __| |/ _ \  |  _| | '_ \ / _` | | '_ \ / _ \   #
#   | |_) | | | (_| \__ \ | (_) | | |___| | | | (_| | | | | |  __/   #
#   |____/|_|  \__,_|___/_|\___/  |_____|_| |_|\__, |_|_| |_|\___|   #
#                                              |___/                 #
######################################################################

cmake_minimum_required(VERSION 3.28.1)

project(BrasioEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0 -fno-inline")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -Wno-error=maybe-uninitialized")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(_validation_default OFF)
else()
    set(_validation_default ON)
endif()
option(BRASIO_ENABLE_VALIDATION "Enable Vulkan validation layers" ${_validation_default})

add_compile_options(-Wall -Wextra -Werror -Wvla -pedantic -Wold-style-cast)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

if(BRASIO_ENABLE_VALIDATION)
    add_compile_definitions(BRASIO_ENABLE_VALIDATION_LAYERS)
    message(STATUS "Vulkan validation layers: ENABLED")
else()
    message(STATUS "Vulkan validation layers: DISABLED")
endif()

find_package(OpenGL REQUIRED)

find_package(glfw3 3.3 REQUIRED)

find_package(GLEW REQUIRED)

find_package(Vulkan REQUIRED)

find_package(yaml-cpp REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
