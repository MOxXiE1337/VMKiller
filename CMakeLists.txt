cmake_minimum_required(VERSION 3.8)
project(VMKiller VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Options

option(VMK_BUILD_TOOLS "Build tools" ON)
option(BUILD_SHARED_LIBS "" ON)

###########

### Dependencies

# glfw
add_subdirectory("dependencies/glfw")

# freetype
add_subdirectory("dependencies/freetype")

# sqlite cpp
add_subdirectory("dependencies/SQLiteCpp")

################

### Modules

# vmkres
add_subdirectory("modules/vmkres")

###########


### Tools

if (VMK_BUILD_TOOLS)
	add_subdirectory("tools/vmkres_editor")
endif()

#########

# install settings
install( TARGETS  SQLiteCpp  RUNTIME  DESTINATION bin)
install( TARGETS  sqlite3  RUNTIME  DESTINATION bin)