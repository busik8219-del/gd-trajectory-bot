cmake_minimum_required(VERSION 3.13.4)

project(trajectory_ai)

# Сначала проверяем системную переменную окружения (напрямую от Geode CLI)
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK "$ENV{GEODE_SDK}")
endif()

# Если CMake запускается внутри кастомного экшена, SDK часто лежит в подпапке cli-profile/sdk
if(NOT DEFINED GEODE_SDK AND EXISTS "${CMAKE_SOURCE_DIR}/cli-profile/sdk")
    set(GEODE_SDK "${CMAKE_SOURCE_DIR}/cli-profile/sdk")
endif()

# Если всё еще не нашли, пробуем дефолтные пути для разных систем
if(NOT DEFINED GEODE_SDK)
    if(WIN32)
        set(GEODE_SDK "$ENV{USERPROFILE}/.geode/sdk")
    else()
        set(GEODE_SDK "$ENV{HOME}/.geode/sdk")
    endif()
endif()

# Выведем путь в лог сборки, чтобы мы его точно видели при отладке
message(STATUS "Using Geode SDK Path: ${GEODE_SDK}")

# Добавляем в пути поиска
list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}")
set(Geode_DIR "${GEODE_SDK}")

find_package(Geode REQUIRED)

add_geode_mod(
    trajectory_ai
    RESOURCES
        about.md
    SOURCES
        main.cpp
)
