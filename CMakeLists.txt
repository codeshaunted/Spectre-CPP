cmake_minimum_required(VERSION 3.8)
project("Spectre")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(Spectre)
include_directories(Spectre/third_party/wren/src/include)

add_executable(Spectre Spectre/main.cc
        Spectre/command.cc
        Spectre/command.h
        Spectre/component.cc
        Spectre/component.h
        Spectre/logger.cc
        Spectre/logger.h
        Spectre/object.cc
        Spectre/object.h
        Spectre/object_manager.cc
        Spectre/object_manager.h
        Spectre/transform_component.cc
        Spectre/transform_component.h
        Spectre/world.h
        )

LINK_DIRECTORIES(Spectre/third_party/wren/lib)
target_link_libraries(Spectre libwren) 
