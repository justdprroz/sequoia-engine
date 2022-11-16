cmake_minimum_required(VERSION 3.17)

project(
    "Sequoia Engine"
    VERSION 0.0.0
    DESCRIPTION "Sequoia is a library for c++ 2d games"
)

set (CMAKE_CXX_STANDARD 20)

# Build SFML as static libs and include it
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(${PROJECT_SOURCE_DIR}/SFML)

# use json lib
add_subdirectory(${PROJECT_SOURCE_DIR}/JSON)

set(
    SEQUIOA_SOURCES
    src/Render/Render.cpp
    src/Render/Renderer.cpp
    src/World/Block.cpp
    src/World/Chunk.cpp
    src/World/Entity.cpp
    src/World/Player.cpp
    src/World/World.cpp
)

add_library(sequoia STATIC ${SEQUIOA_SOURCES})

target_link_libraries(sequoia sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)

target_include_directories(sequoia PUBLIC "src")