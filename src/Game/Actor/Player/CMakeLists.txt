add_subdirectory(AI)
add_subdirectory(Action)

target_sources(uking PRIVATE
  actPlayerBase.cpp
  actPlayerBase.h
  actPlayerInfo.cpp
  actPlayerInfo.h
  actPlayerInfoBase.cpp
  actPlayerInfoStub.cpp
)
