cmake_minimum_required(VERSION 3.10)
project(uking CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(uking
  src/Game/Action/actionSetLinkTagBasic.cpp
  src/Game/Action/actionSetLinkTagBasic.h

  src/KingSystem/ActorSystem/actActor.h
  src/KingSystem/ActorSystem/actActorCreator.cpp
  src/KingSystem/ActorSystem/actActorCreator.h
  src/KingSystem/ActorSystem/actActorFactory.cpp
  src/KingSystem/ActorSystem/actActorFactory.h
  src/KingSystem/ActorSystem/actActorLinkConstDataAccess.cpp
  src/KingSystem/ActorSystem/actActorLinkConstDataAccess.h
  src/KingSystem/ActorSystem/actAiAction.cpp
  src/KingSystem/ActorSystem/actAiAction.h
  src/KingSystem/ActorSystem/actAiClass.cpp
  src/KingSystem/ActorSystem/actAiClass.h
  src/KingSystem/ActorSystem/actAiParam.cpp
  src/KingSystem/ActorSystem/actAiParam.h
  src/KingSystem/ActorSystem/actBaseProc.cpp
  src/KingSystem/ActorSystem/actBaseProc.h
  src/KingSystem/ActorSystem/actBaseProcJob.cpp
  src/KingSystem/ActorSystem/actBaseProcJob.h
  src/KingSystem/ActorSystem/actBaseProcJobHandler.cpp
  src/KingSystem/ActorSystem/actBaseProcJobHandler.h
  src/KingSystem/ActorSystem/actBaseProcLinkDataMgr.cpp
  src/KingSystem/ActorSystem/actBaseProcLinkDataMgr.h
  src/KingSystem/ActorSystem/actBaseProcMap.cpp
  src/KingSystem/ActorSystem/actBaseProcMap.h
  src/KingSystem/ActorSystem/actBaseProcMgr.cpp
  src/KingSystem/ActorSystem/actBaseProcMgr.h
  src/KingSystem/ActorSystem/actBaseProcUnit.cpp
  src/KingSystem/ActorSystem/actBaseProcUnit.h

  src/KingSystem/MessageSystem/mesTransceiver.h

  src/KingSystem/Terrain/teraSystem.h

  src/KingSystem/Utils/Debug.h
  src/KingSystem/Utils/StrTreeMap.h
  src/KingSystem/Utils/Types.h
)

target_include_directories(uking PRIVATE src/)
target_compile_options(uking PRIVATE -fno-rtti -fno-exceptions)
target_compile_options(uking PRIVATE -Wall -Wextra)
target_compile_options(uking PRIVATE -fno-strict-aliasing)
target_compile_options(uking PRIVATE -Wno-invalid-offsetof)

include_directories(lib/NintendoSDK/include)

add_subdirectory(lib/sead)
target_link_libraries(uking PUBLIC sead)

add_subdirectory(lib/agl)
target_link_libraries(uking PUBLIC agl)
