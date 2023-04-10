cmake_minimum_required(VERSION 3.18)
project(interactive_voronoi)

add_executable(interactive_voronoi src/main.c)
target_link_libraries(interactive_voronoi PRIVATE SDL2)
target_include_directories(interactive_voronoi PRIVATE include)
target_sources(interactive_voronoi PRIVATE src/point.c)
