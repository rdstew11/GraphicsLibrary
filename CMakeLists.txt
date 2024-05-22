cmake_minimum_required(VERSION 3.27)
project(GraphicsLibrary C)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(GraphicsLibrary main.c glad.c)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GraphicsLibrary "C:/opt/msys2/mingw64/lib/libglfw3dll.a")