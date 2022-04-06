project(gsys CXX ASM)

add_library(gsys OBJECT
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedProjLight.h
  include/gsys/gsysMaskedSpotLight.h
  include/gsys/gsysModel.h
  include/gsys/gsysModelAccessKey.h
  include/gsys/gsysModelNW.h
  include/gsys/gsysModelSceneConfig.h
  include/gsys/gsysModelUnit.h
  include/gsys/gsysModelUnitDrawArray.h
  include/gsys/gsysOfxLensFlareRig.h
  include/gsys/gsysORUtil.h
  include/gsys/gsysParticleConfig.h
  include/gsys/gsysPointLight.h
  include/gsys/gsysSpotLight.h

  src/gsys/gsysModelAccessKey.cpp
  src/gsys/gsysModelSceneConfig.cpp
  src/gsys/gsysParticleConfig.cpp
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
