cmake_minimum_required(VERSION 3.23)

project(grep++)

add_executable(grep++)

target_sources(grep++
        PRIVATE
        src/main.cpp
        src/config.cpp
        src/printing.cpp
        src/string_stuff.cpp
        src/util.cpp
)
