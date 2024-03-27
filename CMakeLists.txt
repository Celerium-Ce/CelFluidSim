cmake_minimum_required(VERSION 3.28.4)
project(celfluidsim VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(celfluidsim src/config.h src/main.cpp src/glad.c)

target_include_directories(celfluidsim PRIVATE dependencies)

target_link_libraries(celfluidsim glfw OpenGL::GL)
