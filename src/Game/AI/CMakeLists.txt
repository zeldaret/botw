add_subdirectory(Action)
add_subdirectory(Query)

target_sources(uking PRIVATE
  aiQueryFactories.cpp
  aiQueryFactories.h
)
