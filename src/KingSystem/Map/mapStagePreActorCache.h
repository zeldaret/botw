#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace ksys::gfx {
class ForestRenderer;
}

namespace ksys::map {

// TODO
class StagePreActorCache {
    SEAD_SINGLETON_DISPOSER(StagePreActorCache)
    StagePreActorCache();

public:
    auto* getForestRenderer() { return mForestRenderer; }

private:
    gfx::ForestRenderer* mForestRenderer;
};

}  // namespace ksys::map
