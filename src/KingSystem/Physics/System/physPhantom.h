#pragma once

#include <Havok/Physics2012/Dynamics/Phantom/hkpAabbPhantom.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class LayerMaskBuilder;

class Phantom {
    SEAD_RTTI_BASE(Phantom)
public:
    /// @param havok_phantom If null, a hkpAabbPhantom will be automatically created.
    static Phantom* make(sead::Heap* heap, const sead::BoundBox3f& aabb,
                         ContactLayerType layer_type, const LayerMaskBuilder* layer_mask_builder,
                         hkpAabbPhantom* havok_phantom = nullptr);
    static void free(Phantom* phantom);

    Phantom(const sead::BoundBox3f& aabb, ContactLayerType layer_type);

    virtual ~Phantom() = default;

    hkpAabbPhantom* getHavokPhantom() const { return mHavokPhantom; }
    const sead::BoundBox3f& getAabb() const { return mAabb; }
    ContactLayerType getLayerType() const { return mLayerType; }
    sead::BitFlag32 getLayerMask() const { return mLayerMask; }

    /// @param havok_phantom If null, a hkpAabbPhantom will be automatically created.
    void initHavokPhantom(hkpAabbPhantom* havok_phantom = nullptr);
    void setLayerMask(const LayerMaskBuilder& builder);

    bool isAddedToWorld() const;
    void addPhantomToWorld();
    void removePhantomFromWorld();

    /// Use this to update the collision filter info and the AABB of the Havok phantom.
    void updateHavokFilterInfoAndAabb();

private:
    hkpAabbPhantom* mHavokPhantom{};
    sead::BoundBox3f mAabb;
    ContactLayerType mLayerType;
    sead::BitFlag32 mLayerMask;
    bool mDirtyLayerMask = false;
};

class WorldBorderPhantom : public hkpAabbPhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(WorldBorderPhantom)

    WorldBorderPhantom();
    ~WorldBorderPhantom() override;
    void addOverlappingCollidable(hkpCollidable* collidable) override;
};

}  // namespace ksys::phys
