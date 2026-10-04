add_subdirectory(Actor)
add_subdirectory(Cooking)
add_subdirectory(DLC)
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
