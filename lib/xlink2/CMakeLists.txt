project(xlink2 CXX ASM)

add_library(xlink2 OBJECT
  include/xlink2/xlink2.h
  src/dummy.cpp
)

target_compile_options(xlink2 PRIVATE -fno-exceptions)
target_compile_options(xlink2 PRIVATE -fno-strict-aliasing)
target_compile_options(xlink2 PRIVATE -Wno-invalid-offsetof)
target_include_directories(xlink2 PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(xlink2 PUBLIC sead)
