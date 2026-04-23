cmake_minimum_required(VERSION 3.23)

project(grep++)

add_executable(grep++)

target_sources(grep++
        PRIVATE
        main.cpp
        config.cpp
        printing.cpp
        string_stuff.cpp
        util.cpp
)
