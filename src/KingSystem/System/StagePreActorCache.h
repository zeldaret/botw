#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace ksys::gfx {
class ForestRenderer;
}

namespace ksys::map {
class LazyTraverseList;
}

namespace ksys {

// TODO
class StagePreActorCache {
    SEAD_SINGLETON_DISPOSER(StagePreActorCache)
    StagePreActorCache();

public:
    map::LazyTraverseList* getObjects() const { return mObjects; }
    auto* getForestRenderer() { return mForestRenderer; }

private:
    char _0[0x20];
    map::LazyTraverseList* mObjects;
    gfx::ForestRenderer* mForestRenderer;
};

}  // namespace ksys
