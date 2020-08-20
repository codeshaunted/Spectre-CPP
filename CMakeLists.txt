cmake_minimum_required(VERSION 3.8)
project(Spectre C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("-- Compiling Spectre")

if (NOT EXISTS output)
    file(MAKE_DIRECTORY output)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)

include_directories(Spectre/source)
add_subdirectory(Spectre/third_party)

add_executable(Spectre Spectre/source/main.cc
        Spectre/source/command.cc
        Spectre/source/command.h
        Spectre/source/component.cc
        Spectre/source/component.h
        Spectre/source/logger.cc
        Spectre/source/logger.h
        Spectre/source/object.cc
        Spectre/source/object.h
        Spectre/source/object_manager.cc
        Spectre/source/object_manager.h
        Spectre/source/transform_component.cc
        Spectre/source/transform_component.h
        Spectre/source/world.h
        Spectre/source/world.cc
        )
set_target_properties(Spectre PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Spectre wren_lib glfw)