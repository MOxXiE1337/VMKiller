cmake_minimum_required(VERSION 3.8)
project(VMKiller VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "" ON)

# vmksdk
include_directories("vmksdk/vmkcpp")

# vmk modules
add_subdirectory("modules")

# glfw
add_subdirectory("dependencies/glfw")

# freetype
add_subdirectory("dependencies/freetype")

# zydis
option(ZYDIS_BUILD_SHARED_LIB "" ON)
add_subdirectory("dependencies/zydis")

# sqlite cpp
option(BUILD_SHARED_LIBS "" ON)
add_subdirectory("dependencies/SQLiteCpp")


# install settings
install( TARGETS  vmkui  RUNTIME DESTINATION bin)


install( TARGETS  SQLiteCpp  RUNTIME  DESTINATION bin)
install( TARGETS  sqlite3  RUNTIME  DESTINATION bin)