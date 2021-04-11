cmake_minimum_required(VERSION 3.13)
project(uking CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
  # Required to silence "unused argument" warnings for -stdlib=libc++ when using distcc
  add_compile_options(-Wno-unused-command-line-argument)
  # Required to fix source paths in debug info when using distcc
  add_compile_options(-fdebug-prefix-map=/tmp=${CMAKE_CURRENT_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(uking)
target_include_directories(uking PRIVATE src)
target_compile_options(uking PRIVATE -fno-rtti -fno-exceptions)
target_compile_options(uking PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(uking PRIVATE -Wno-unused-parameter -Wno-unused-private-field)
target_compile_options(uking PRIVATE -fno-strict-aliasing)
target_compile_options(uking PRIVATE -Wno-invalid-offsetof)

add_subdirectory(lib/NintendoSDK)
target_link_libraries(uking PUBLIC NintendoSDK)

add_subdirectory(lib/sead)
target_link_libraries(uking PUBLIC sead)

add_subdirectory(lib/agl)
target_link_libraries(uking PUBLIC agl)

add_subdirectory(lib/aal)
target_link_libraries(uking PRIVATE aal)

add_subdirectory(lib/EventFlow)
target_link_libraries(uking PRIVATE evfl)

add_subdirectory(src)
