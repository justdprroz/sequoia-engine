cmake_minimum_required(VERSION 3.17)

# Project definition
project(
    "Sequoia Engine"
    VERSION 0.0.0
    DESCRIPTION "Sequoia is a library for c++ 2d games"
)

include_directories("src")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

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