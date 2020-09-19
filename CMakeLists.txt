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
  src/Game/AI/Action/actionSetInstEventFlag.cpp
  src/Game/AI/Action/actionSetInstEventFlag.h
  src/Game/AI/Action/actionSetLinkTagBasic.cpp
  src/Game/AI/Action/actionSetLinkTagBasic.h

  src/Game/DLC/aoc2.cpp
  src/Game/DLC/aoc2.h

  src/KingSystem/ActorSystem/actActor.h
  src/KingSystem/ActorSystem/actActorConstDataAccess.cpp
  src/KingSystem/ActorSystem/actActorConstDataAccess.h
  src/KingSystem/ActorSystem/actActorCreator.cpp
  src/KingSystem/ActorSystem/actActorCreator.h
  src/KingSystem/ActorSystem/actActorFactory.cpp
  src/KingSystem/ActorSystem/actActorFactory.h
  src/KingSystem/ActorSystem/actActorLinkConstDataAccess.cpp
  src/KingSystem/ActorSystem/actActorLinkConstDataAccess.h
  src/KingSystem/ActorSystem/actActorParamMgr.h
  src/KingSystem/ActorSystem/actAiAction.cpp
  src/KingSystem/ActorSystem/actAiAction.h
  src/KingSystem/ActorSystem/actAiClass.cpp
  src/KingSystem/ActorSystem/actAiClass.h
  src/KingSystem/ActorSystem/actAiParam.cpp
  src/KingSystem/ActorSystem/actAiParam.h
  src/KingSystem/ActorSystem/actBaseProc.cpp
  src/KingSystem/ActorSystem/actBaseProc.h
  src/KingSystem/ActorSystem/actBaseProcHandle.cpp
  src/KingSystem/ActorSystem/actBaseProcHandle.h
  src/KingSystem/ActorSystem/actBaseProcJob.cpp
  src/KingSystem/ActorSystem/actBaseProcJob.h
  src/KingSystem/ActorSystem/actBaseProcJobHandler.cpp
  src/KingSystem/ActorSystem/actBaseProcJobHandler.h
  src/KingSystem/ActorSystem/actBaseProcLink.cpp
  src/KingSystem/ActorSystem/actBaseProcLink.h
  src/KingSystem/ActorSystem/actBaseProcMap.cpp
  src/KingSystem/ActorSystem/actBaseProcMap.h
  src/KingSystem/ActorSystem/actBaseProcMgr.cpp
  src/KingSystem/ActorSystem/actBaseProcMgr.h
  src/KingSystem/ActorSystem/actBaseProcUnit.cpp
  src/KingSystem/ActorSystem/actBaseProcUnit.h
  src/KingSystem/ActorSystem/actTag.h

  src/KingSystem/Map/mapTypes.h
  src/KingSystem/Map/mapMubinIter.cpp
  src/KingSystem/Map/mapMubinIter.h
  src/KingSystem/Map/mapObject.cpp
  src/KingSystem/Map/mapObject.h

  src/KingSystem/MessageSystem/mesTransceiver.h

  src/KingSystem/Resource/GeneralParamList/resGParamListObject.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectAttackInterval.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectBindBone.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyShown.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectRod.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectSandworm.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.cpp
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponOption.h
  src/KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponThrow.h
  src/KingSystem/Resource/GeneralParamList/resGParamListTraits.h
  src/KingSystem/Resource/resCurrentResNameMgr.cpp
  src/KingSystem/Resource/resCurrentResNameMgr.h
  src/KingSystem/Resource/resEntryFactory.cpp
  src/KingSystem/Resource/resEntryFactory.h
  src/KingSystem/Resource/resResource.cpp
  src/KingSystem/Resource/resResource.h
  src/KingSystem/Resource/resResourceActorLink.cpp
  src/KingSystem/Resource/resResourceActorLink.h
  src/KingSystem/Resource/resResourceAIProgram.cpp
  src/KingSystem/Resource/resResourceAIProgram.h
  src/KingSystem/Resource/resResourceArchive.cpp
  src/KingSystem/Resource/resResourceArchive.h
  src/KingSystem/Resource/resResourceDemo.cpp
  src/KingSystem/Resource/resResourceDemo.h
  src/KingSystem/Resource/resResourceDrop.cpp
  src/KingSystem/Resource/resResourceDrop.h
  src/KingSystem/Resource/resResourceGParamList.cpp
  src/KingSystem/Resource/resResourceGParamList.h
  src/KingSystem/Resource/resResourceLod.cpp
  src/KingSystem/Resource/resResourceLod.h
  src/KingSystem/Resource/resResourceRecipe.cpp
  src/KingSystem/Resource/resResourceRecipe.h

  src/KingSystem/Terrain/teraSystem.h

  src/KingSystem/Utils/Thread/Event.cpp
  src/KingSystem/Utils/Thread/Event.h
  src/KingSystem/Utils/Thread/GameTaskThread.cpp
  src/KingSystem/Utils/Thread/GameTaskThread.h
  src/KingSystem/Utils/Thread/ManagedTask.cpp
  src/KingSystem/Utils/Thread/ManagedTask.h
  src/KingSystem/Utils/Thread/ManagedTaskHandle.cpp
  src/KingSystem/Utils/Thread/ManagedTaskHandle.h
  src/KingSystem/Utils/Thread/Task.cpp
  src/KingSystem/Utils/Thread/Task.h
  src/KingSystem/Utils/Thread/TaskMgr.cpp
  src/KingSystem/Utils/Thread/TaskMgr.h
  src/KingSystem/Utils/Thread/TaskQueueBase.cpp
  src/KingSystem/Utils/Thread/TaskQueueBase.h
  src/KingSystem/Utils/Thread/TaskQueue.cpp
  src/KingSystem/Utils/Thread/TaskQueue.h
  src/KingSystem/Utils/Thread/TaskQueueLock.cpp
  src/KingSystem/Utils/Thread/TaskQueueLock.h
  src/KingSystem/Utils/Thread/TaskThread.cpp
  src/KingSystem/Utils/Thread/TaskThread.h
  src/KingSystem/Utils/Byaml.cpp
  src/KingSystem/Utils/Byaml.h
  src/KingSystem/Utils/ByamlLocal.cpp
  src/KingSystem/Utils/ByamlLocal.h
  src/KingSystem/Utils/ByamlUtil.cpp
  src/KingSystem/Utils/Debug.h
  src/KingSystem/Utils/FixedString.h
  src/KingSystem/Utils/HashUtil.h
  src/KingSystem/Utils/HeapUtil.cpp
  src/KingSystem/Utils/HeapUtil.h
  src/KingSystem/Utils/ParamIO.h
  src/KingSystem/Utils/StrTreeMap.h
  src/KingSystem/Utils/Types.h
)

target_include_directories(uking PRIVATE src/)
target_compile_options(uking PRIVATE -fno-rtti -fno-exceptions)
target_compile_options(uking PRIVATE -Wall -Wextra)
target_compile_options(uking PRIVATE -fno-strict-aliasing)
target_compile_options(uking PRIVATE -Wno-invalid-offsetof)

add_subdirectory(lib/NintendoSDK)
target_link_libraries(uking PUBLIC NintendoSDK)

add_subdirectory(lib/sead)
target_link_libraries(uking PUBLIC sead)

add_subdirectory(lib/agl)
target_link_libraries(uking PUBLIC agl)
