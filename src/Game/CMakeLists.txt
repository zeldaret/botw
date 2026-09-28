add_subdirectory(Actor)
add_subdirectory(AOC)
add_subdirectory(AutoPlacement)
add_subdirectory(Cooking)
add_subdirectory(Scene)
add_subdirectory(UI)

target_sources(uking PRIVATE
  gameItemUtils.cpp
  gameItemUtils.h
  gamePlayReport.cpp
  gamePlayReport.h
  E3Mgr.cpp
  E3Mgr.h
)
