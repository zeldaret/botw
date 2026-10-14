#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class BoxWaterShape;

class BoxWaterRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(BoxWaterRigidBody, RigidBodyFromShape)
public:
    static BoxWaterRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    BoxWaterRigidBody(hkpRigidBody* hk_body, BoxWaterShape* shape, ContactLayerType layer_type,
                      const sead::SafeString& name, bool unused, sead::Heap* heap);
    ~BoxWaterRigidBody() override;

    /// Set the box extents and trigger a shape update.
    void setExtents(const sead::Vector3f& extents);
    /// Set the box translation and trigger a shape update.
    void setTranslate(const sead::Vector3f& translate);

    const sead::Vector3f& getExtents() const;
    const sead::Vector3f& getTranslate() const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    float getVolume() override;

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

    BoxWaterShape* mShape;
    u32 _d8{};
};

}  // namespace ksys::phys
