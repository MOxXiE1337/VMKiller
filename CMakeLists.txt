cmake_minimum_required(VERSION 3.8)
project(VMKiller VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# freetype
option(BUILD_SHARED_LIBS "" ON)
add_subdirectory("dependencies/freetype")

# zydis
option(ZYDIS_BUILD_SHARED_LIB "" ON)
add_subdirectory("dependencies/zydis")
