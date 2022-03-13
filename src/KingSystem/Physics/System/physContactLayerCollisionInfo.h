#pragma once

#include <container/seadOffsetList.h>
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

/// Tracks colliding bodies that belong to a specific contact layer.
class ContactLayerCollisionInfo : public CollisionInfoBase {
public:
    explicit ContactLayerCollisionInfo(ContactLayer layer);
    ~ContactLayerCollisionInfo() override;

    ContactLayer getLayer() const { return mLayer; }

    sead::OffsetList<CollidingBodies>& getCollidingBodies() { return mCollidingBodies; }
    const sead::OffsetList<CollidingBodies>& getCollidingBodies() const { return mCollidingBodies; }

private:
    ContactLayer mLayer;
    sead::OffsetList<CollidingBodies> mCollidingBodies;
};

}  // namespace ksys::phys
