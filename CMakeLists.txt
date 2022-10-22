cmake_minimum_required(VERSION 3.17)

project(
    "Sequoia Engine"
    VERSION 0.0.0
    DESCRIPTION "Sequoia is a library for c++ 2d games"
)

set (CMAKE_CXX_STANDARD 20)

include_directories("src")

set(
    SEQUIOA_SOURCES
    src/Render.cpp
    src/Renderer.cpp
    src/World.cpp
)

add_library(
    sequoia STATIC
    ${SEQUIOA_SOURCES}
)