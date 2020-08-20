# Bullet Code
set(BUILD_PYBULLET FALSE)
set(BUILD_EXTRAS FALSE)

if (LINUX)
    if (EXISTS /usr/lib/x86_64-linux-gnu/libGL.so OR /usr/lib/x86_64-linux-gnu/libGLX.so OR /usr/lib/x86_64-linux-gnu/libOpenGL.so)
        if (EXISTS /usr/lib/x86_64-linux-gnu/libGLX.so OR /usr/lib/x86_64-linux-gnu/libOpenGL.so)
            set(OpenGL_GL_PREFERENCE GLVND)
        else()
            set(OpenGL_GL_PREFERENCE LEGACY)
        endif()
    else()
        message(FATAL_ERROR "X11/XOrg isn't installed please install it")
    endif()
elseif(APPLE)
    find_package(COCOA_LIBRARY Cocoa)
    if (NOT COCOA_LIBRARY_FOUND)
        message(FATAL_ERROR "Cocoa not found please install it")
    endif()
endif()

message("-- Configured Bullet")

add_subdirectory(bullet3)

message("-- Generated Bullet CMake files")

include_directories(${BULLET_PHYSICS_SOURCE_DIR}/src)

# GLFW Code
set(GLFW_BUILD_DOCS FALSE)

add_subdirectory(glfw)

# Wren Code

include_directories(wren/src/vm)
include_directories(wren/src/optional)
include_directories(wren/src/include)

add_library(wren_lib SHARED
        wren/src/vm/wren_common.h
        wren/src/vm/wren_compiler.c
        wren/src/vm/wren_compiler.h
        wren/src/vm/wren_core.c
        wren/src/vm/wren_core.h
        wren/src/vm/wren_debug.c
        wren/src/vm/wren_debug.h
        wren/src/vm/wren_opcodes.h
        wren/src/vm/wren_primitive.c
        wren/src/vm/wren_primitive.h
        wren/src/vm/wren_utils.c
        wren/src/vm/wren_utils.h
        wren/src/vm/wren_value.c
        wren/src/vm/wren_value.h
        wren/src/vm/wren_vm.c
        wren/src/vm/wren_vm.h
        wren/src/optional/wren_opt_meta.c
        wren/src/optional/wren_opt_meta.h
        wren/src/optional/wren_opt_random.c
        wren/src/optional/wren_opt_random.h
        )

set_target_properties(wren_lib PROPERTIES LINKER_LANGUAGE C)

message("-- Generated Wren CMake Files")