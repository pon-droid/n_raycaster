cmake_minimum_required(VERSION 3.5)

project(t_raycaster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SDL2 REQUIRED)

add_executable(t_raycaster main.cpp caster.h caster.cpp)
target_link_libraries(t_raycaster SDL2::SDL2)
