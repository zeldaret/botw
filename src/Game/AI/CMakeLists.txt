add_subdirectory(Action)
add_subdirectory(AI)
add_subdirectory(Query)

target_sources(uking PRIVATE
  aiActionFactories.cpp
  aiActionFactories.h
  aiAiFactories.cpp
  aiAiFactories.h
  aiQueryFactories.cpp
  aiQueryFactories.h
)
