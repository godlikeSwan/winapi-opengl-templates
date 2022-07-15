cmake_minimum_required(VERSION 3.10)

project(2d VERSION 1.0)

add_executable(2d WIN32 2d.cpp scene.cpp)

# for static linking

# set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.a;.dll.a")
# target_compile_options(2d PUBLIC /MT)
# target_link_options(2d PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)

find_package(OpenGL REQUIRED)

target_link_libraries(2d opengl32.lib)

target_include_directories(2d PUBLIC "${PROJECT_BINARY_DIR}")

set_target_properties(2d PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
