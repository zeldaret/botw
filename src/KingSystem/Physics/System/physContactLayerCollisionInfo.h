#pragma once

#include <container/seadOffsetList.h>
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

/// Tracks contact points for a contact layer.
class ContactLayerCollisionInfo : public CollisionInfoBase {
public:
    explicit ContactLayerCollisionInfo(ContactLayer layer);
    ~ContactLayerCollisionInfo() override;

    ContactLayer getLayer() const { return mLayer; }

    auto& getList() { return mList; }
    const auto& getList() const { return mList; }

private:
    ContactLayer mLayer;
    // FIXME: type
    sead::OffsetList<void*> mList;
};

}  // namespace ksys::phys
