cmake_minimum_required(VERSION 3.5)
project(tutorial VERSION 0.0.1)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(glad)
add_executable(tutorial render.cpp)
target_link_libraries(
tutorial PUBLIC
glfw
glad
dl
)