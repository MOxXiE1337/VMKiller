cmake_minimum_required(VERSION 3.8)
project(vmkres VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("../vmkshared/vmkshared")
include_directories("../vmkutils/vmkutils")

add_compile_definitions(VMK_EXPORT)

set(VMKRES_SRCS 
	"vmkres/vmkres/Resource.cpp")

add_library(${PROJECT_NAME} SHARED ${VMKRES_SRCS})