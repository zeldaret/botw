project(gsys CXX ASM)

add_library(gsys OBJECT
  src/ParticleConfig.cpp
)

target_compile_options(gsys PRIVATE -fno-exceptions)
target_compile_options(gsys PRIVATE -fno-strict-aliasing)
target_compile_options(gsys PRIVATE -Wno-invalid-offsetof)
target_include_directories(gsys PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(gsys PUBLIC sead)

if(NOT TARGET agl)
  add_subdirectory(../agl)
endif()
target_link_libraries(gsys PUBLIC agl)
