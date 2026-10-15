#pragma once
#include <basis/seadTypes.h>
namespace sead {
class Heap;
}
namespace ksys::map {
class RailFactory;
// These bind the original global factory and its existing lifetime functions.
extern RailFactory* gRailFactory;
RailFactory* createRailFactory(sead::Heap* heap);
void destroyRailFactory();
}  // namespace ksys::map
