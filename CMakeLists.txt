cmake_minimum_required(VERSION 3.8)
project(VMKiller VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# freetype
set(BUILD_SHARED_LIBS true)
add_subdirectory("dependencies/freetype")


add_subdirectory("dependencies/imgui-cmake")
