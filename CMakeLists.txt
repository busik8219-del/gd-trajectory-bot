cmake_minimum_required(VERSION 3.13.4)

project(trajectory_ai)

# Добавляем путь к Geode SDK, чтобы CMake сразу его нашел
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

add_geode_mod(
    trajectory_ai
    RESOURCES
        about.md
    SOURCES
        main.cpp
)
