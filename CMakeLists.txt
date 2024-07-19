cmake_minimum_required(VERSION 3.27)
project(GraphicsLibrary C)

set(CMAKE_C_STANDARD 11)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CGLM cglm)


find_library(GLFW glfw3)
find_library(GDI gdi32)
find_library(OpenGL opengl32)

add_executable(GraphicsLibrary ${SRC_DIR}/main.c glad.c
        src/shaderprogram.h
        src/shaderprogram.c
)

add_subdirectory(external/cglm)

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/external")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GraphicsLibrary ${CGLM})
target_link_libraries(GraphicsLibrary ${GLFW})
target_link_libraries(GraphicsLibrary ${GDI})
target_link_libraries(GraphicsLibrary ${OpenGL})

