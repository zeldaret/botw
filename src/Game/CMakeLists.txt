add_subdirectory(Actor)
add_subdirectory(AI)
add_subdirectory(Damage)
add_subdirectory(DLC)
add_subdirectory(UI)

target_sources(uking PRIVATE
  gameScene.cpp
  gameScene.h
  gameStageInfo.cpp
  gameStageInfo.h
)
