cmake_minimum_required(VERSION 3.8)
project("Spectre")

set(CMAKE_CXX_STANDARD 17)

include_directories(Spectre)

add_executable(Spectre Spectre/main.cc
        Spectre/command.cc
        Spectre/command.h
        Spectre/command_id.h
        Spectre/component.cc
        Spectre/component.h
        Spectre/component_id.h
        Spectre/logger.cc
        Spectre/logger.h
        Spectre/object.cc
        Spectre/object.h
        Spectre/objectmanager.cc
        Spectre/objectmanager.h
        Spectre/observer.cc
        Spectre/observer.h
        Spectre/physics_component.cc
        Spectre/physics_component.h
        Spectre/subject.cc
        Spectre/subject.h
        Spectre/world.h
        )

LINK_DIRECTORIES(Spectre/third_party/wren/lib)
target_link_libraries(Spectre libwren)