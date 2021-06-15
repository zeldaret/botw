project(aal CXX ASM)

add_library(aal OBJECT
  src/dummy.cpp
)

target_compile_options(aal PRIVATE -fno-exceptions)
target_compile_options(aal PRIVATE -fno-strict-aliasing)
target_compile_options(aal PRIVATE -Wno-invalid-offsetof)
target_include_directories(aal PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(aal PUBLIC sead)
