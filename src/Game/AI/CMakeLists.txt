add_subdirectory(Action)
add_subdirectory(Query)

target_sources(uking PRIVATE
  aiActionFactories.cpp
  aiActionFactories.h
  aiQueryFactories.cpp
  aiQueryFactories.h
)
