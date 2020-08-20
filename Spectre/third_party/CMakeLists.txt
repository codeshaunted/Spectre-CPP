add_subdirectory(glfw)

include_directories(wren/src/vm)
include_directories(wren/src/optional)
include_directories(wren/src/include)

if (NOT EXISTS output)
    file(MAKE_DIRECTORY output)
endif()

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