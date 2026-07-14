cmake_minimum_required(VERSION 3.13.4)

project(trajectory_ai)

# Проверяем путь, который выдал лог, и добавляем путь к собранным бинарникам SDK
if(DEFINED ENV{GEODE_SDK})
    set(GEODE_SDK "$ENV{GEODE_SDK}")
else()
    set(GEODE_SDK "${CMAKE_SOURCE_DIR}/geode-sdk-clone")
endif()

# Отрезаем возможные лишние слеши и собираем точные пути к конфигурации CMake
set(GEODE_SDK_BIN "${GEODE_SDK}/bin/nightly")

message(STATUS "Checking Geode SDK Base Path: ${GEODE_SDK}")
message(STATUS "Checking Geode SDK Binary Path: ${GEODE_SDK_BIN}")

# Передаем оба пути в CMake, чтобы он точно зацепил GeodeConfig.cmake
list(APPEND CMAKE_PREFIX_PATH "${GEODE_SDK}" "${GEODE_SDK_BIN}")
set(Geode_DIR "${GEODE_SDK_BIN}")

find_package(Geode REQUIRED)

add_geode_mod(
    trajectory_ai
    RESOURCES
        about.md
    SOURCES
        main.cpp
)
