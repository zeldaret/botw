if (DEFINED ENV{UKING_CLANG})
    set(UKING_CLANG "$ENV{UKING_CLANG}")
else()
    set(UKING_CLANG "${CMAKE_CURRENT_LIST_DIR}/clang-4.0.1")
endif()

set(NX64_OPT_FLAGS "-O3 -g")
set(NX64_TRIPLE aarch64-linux-elf)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_SYSROOT ${CMAKE_CURRENT_LIST_DIR}/musl)
set(CMAKE_C_COMPILER "${UKING_CLANG}/bin/clang")
set(CMAKE_C_COMPILER_TARGET ${NX64_TRIPLE})
set(CMAKE_CXX_COMPILER "${UKING_CLANG}/bin/clang++")
set(CMAKE_CXX_COMPILER_TARGET ${NX64_TRIPLE})

set(CMAKE_C_FLAGS_RELEASE ${NX64_OPT_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${NX64_OPT_FLAGS})
set(CMAKE_C_FLAGS_RELWITHDEBINFO ${NX64_OPT_FLAGS})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${NX64_OPT_FLAGS})

# Target options
add_compile_options(-mcpu=cortex-a57+fp+simd+crypto+crc)
add_compile_options(-mno-implicit-float)
# Environment
add_compile_options(-stdlib=libc++)
add_compile_options(-fPIC)
# Helps with matching as this causes Clang to emit debug type info even for dynamic classes
# with undefined vtables.
add_compile_options(-fstandalone-debug)

add_definitions(-D SWITCH)
add_definitions(-D NNSDK)
add_definitions(-D MATCHING_HACK_NX_CLANG)

add_link_options(-stdlib=libc++ -nostdlib)
add_link_options(-fPIC -Wl,-Bsymbolic-functions -shared)
if (DEFINED UKING_LINKER)
    message(STATUS "Using custom linker: ${UKING_LINKER}")
    add_link_options(-fuse-ld=${UKING_LINKER})
else()
    # Use lld for performance reasons (and because we don't want a dependency on GNU tools)
    add_link_options(-fuse-ld=lld)
endif()
