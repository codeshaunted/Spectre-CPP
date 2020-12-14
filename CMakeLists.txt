cmake_minimum_required(VERSION 3.8)
project(Spectre LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message("-- Began Spectre CMake")

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (NOT EXISTS output)
    file(MAKE_DIRECTORY output)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/output)

include_directories(Spectre/source)
add_subdirectory(Spectre/third_party)

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)
include_directories(Spectre/third_party/wren/src/include)

include_directories(Spectre/third_party/nlohmann_json/single_include)

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
        Spectre/source/internal_types.cc
        Spectre/source/internal_types.h
        Spectre/source/physics_component.cc
        Spectre/source/physics_component.h
        Spectre/source/wren_component.cc
        Spectre/source/wren_bindings.cc
        Spectre/source/pubsub.cc
        Specture/source/input.cc
        )

set_target_properties(Spectre PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Spectre
        wren_lib
        glfw
        Bullet3Collision
        BulletDynamics
        BulletCollision
        Bullet3OpenCL_clew
        LinearMath
        Bullet3Geometry
        Bullet3Common
        Bullet3Dynamics
        )