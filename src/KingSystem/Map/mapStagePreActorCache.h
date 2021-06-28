#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace ksys::map {

class ForestRenderer {
public:
    s32 x_7(const sead::Vector3f& vec);
};

// TODO
class StagePreActorCache {
    SEAD_SINGLETON_DISPOSER(StagePreActorCache)
    StagePreActorCache();

public:
    auto* getForestRenderer() { return mForestRenderer; }

private:
    ForestRenderer* mForestRenderer;
};

}  // namespace ksys::map
