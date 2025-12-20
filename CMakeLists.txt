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

add_compile_options(-Wall -Wextra -Werror -Wvla -pedantic -Wold-style-cast -g -O0 -fsanitize=address)
add_link_options(-g -O0 -fsanitize=address)

find_package(OpenGL REQUIRED)

find_package(glfw3 3.3 REQUIRED)

find_package(GLEW REQUIRED)

find_package(Vulkan REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
