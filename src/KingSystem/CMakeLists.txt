# Build these first because it contains many source files that take a long time to build.
add_subdirectory(GameData)
add_subdirectory(Resource)

add_subdirectory(ActorSystem)
add_subdirectory(Chemical)
add_subdirectory(Cooking)
add_subdirectory(Ecosystem)
add_subdirectory(Effect)
add_subdirectory(Event)
add_subdirectory(Framework)
add_subdirectory(Map)
add_subdirectory(Mii)
add_subdirectory(Physics)
add_subdirectory(Quest)
add_subdirectory(Sound)
add_subdirectory(System)
add_subdirectory(Terrain)
add_subdirectory(Utils)
add_subdirectory(World)
add_subdirectory(XLink)

target_sources(uking PRIVATE
  ksys.cpp
  ksys.h
)
