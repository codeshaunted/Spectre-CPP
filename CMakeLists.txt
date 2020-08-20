cmake_minimum_required(VERSION 3.8)
project(Spectre C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("-- Compiling Spectre")

include_directories(source)
add_subdirectory(third_party)

add_executable(Spectre source/main.cc
        source/command.cc
        source/command.h
        source/component.cc
        source/component.h
        source/logger.cc
        source/logger.h
        source/object.cc
        source/object.h
        source/object_manager.cc
        source/object_manager.h
        source/transform_component.cc
        source/transform_component.h
        source/world.h
        source/world.cc
        )
set_target_properties(Spectre PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Spectre wren_lib glfw)