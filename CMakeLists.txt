cmake_minimum_required(VERSION 3.13.4)

project(trajectory_ai)

# Явно указываем стандартный путь установки Geode SDK на виртуальной машине GitHub (Windows)
if(NOT DEFINED GEODE_SDK AND DEFINED ENV{USERPROFILE})
    set(GEODE_SDK "$ENV{USERPROFILE}/.geode/sdk")
endif()

# Если путь был передан через переменную окружения напрямую
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK "$ENV{GEODE_SDK}")
endif()

# Добавляем найденный путь в поиск пакетов CMake
list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}")

find_package(Geode REQUIRED)

add_geode_mod(
    trajectory_ai
    RESOURCES
        about.md
    SOURCES
        main.cpp
)
