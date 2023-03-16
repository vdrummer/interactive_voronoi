cmake_minimum_required(VERSION 3.18)
project(interactive_voronoi)

add_executable(interactive_voronoi src/main.c)
target_link_libraries(interactive_voronoi PRIVATE SDL2)
