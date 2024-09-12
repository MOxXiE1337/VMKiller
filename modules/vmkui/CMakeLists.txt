cmake_minimum_required(VERSION 3.8)
project(vmkui VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

include_directories(../vmkui/public)
include_directories(../vmkshared/public)
include_directories(../vmkutils/public)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/imgui)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/imgui/backends)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/freetype/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/glfw/include)

add_compile_definitions(VMK_EXPORT)
add_compile_definitions(IMGUI_ENABLE_FREETYPE)

set(VMKUI_SRCS
	private/Application/Application.cpp)

set(IMGUI_SRCS
	${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_demo.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_draw.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_tables.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/imgui_widgets.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/misc/freetype/imgui_freetype.cpp)

set(IMGUI_BACKEND_SRCS
	${CMAKE_SOURCE_DIR}/dependencies/imgui/backends/imgui_impl_opengl3.cpp
	${CMAKE_SOURCE_DIR}/dependencies/imgui/backends/imgui_impl_glfw.cpp)

add_library(${PROJECT_NAME} SHARED 
	${IMGUI_SRCS}
	${IMGUI_BACKEND_SRCS}
	${VMKUI_SRCS})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	freetype 
	${OPENGL_gl_LIBRARY} 
	glfw)

install(TARGETS freetype RUNTIME DESTINATION VMKiller)
install(TARGETS glfw RUNTIME DESTINATION VMKiller)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION VMKiller)