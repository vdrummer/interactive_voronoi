cmake_minimum_required(VERSION 3.18)
project(interactive_voronoi)

add_subdirectory(libs/unity)

add_executable(interactive_voronoi src/main.c)
target_link_libraries(interactive_voronoi PRIVATE SDL2)
target_include_directories(interactive_voronoi PRIVATE include)
target_sources(interactive_voronoi PRIVATE src/point.c)

add_executable(test_centroid_list src/test_centroid_list.c)
target_include_directories(test_centroid_list PRIVATE include)
target_sources(test_centroid_list PRIVATE src/centroid_list.c)
target_link_libraries(test_centroid_list PRIVATE unity)
target_compile_options(test_centroid_list PRIVATE -g)
