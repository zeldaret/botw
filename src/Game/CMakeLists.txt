add_subdirectory(Actor)
add_subdirectory(AI)
add_subdirectory(Cooking)
add_subdirectory(Damage)
add_subdirectory(DLC)
add_subdirectory(UI)

target_sources(uking PRIVATE
  AirOctaDataMgrTemp.h
  AirOctaDataMgrTemp.cpp
  gameItemUtils.cpp
  gameItemUtils.h
  gamePlayReport.cpp
  gamePlayReport.h
  gameScene.cpp
  gameScene.h
  gameStageInfo.cpp
  gameStageInfo.h
  E3Mgr.cpp
  E3Mgr.h

)
