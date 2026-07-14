cmake_minimum_required(VERSION 3.13.4)

project(trajectory_ai)

find_package(Geode REQUIRED)

add_geode_mod(
    trajectory_ai
    RESOURCES
        about.md
    SOURCES
        main.cpp
)