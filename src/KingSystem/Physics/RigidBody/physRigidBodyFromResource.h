#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class RigidBodyFromResource : public RigidBody {
    SEAD_RTTI_OVERRIDE(RigidBodyFromResource, RigidBody)
public:
    RigidBodyFromResource(float volume, hkpRigidBody* hk_body, ContactLayerType layer_type,
                          sead::Heap* heap, Type type);
    ~RigidBodyFromResource() override;

    bool init(const RigidBodyInstanceParam& param, sead::Heap* heap);

    bool isBvTreeOrStaticCompound() const;
    bool isMaterial(Material material) const;

    float getVolume() override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

protected:
    float updateScale_(float scale, float old_scale) override;
    const hkpShape* getNewHavokShape_() override;

private:
    const hkpShape* mShape = nullptr;
    float mVolume = 1.0;
    float mCurrentScale = 1.0;
    float mNewScale = 1.0;
};

}  // namespace ksys::phys
