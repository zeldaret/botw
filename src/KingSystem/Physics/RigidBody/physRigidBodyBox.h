#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class BoxShape;
struct RigidBodyInstanceParam;

class BoxRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(BoxRigidBody, RigidBodyFromShape)
public:
    static BoxRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    BoxRigidBody(hkpRigidBody* hk_body, BoxShape* shape, ContactLayerType layer_type,
                 const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~BoxRigidBody() override;

    /// Set the box extents and trigger a shape update.
    void setExtents(const sead::Vector3f& extents);
    /// Set the box translation and trigger a shape update.
    void setTranslate(const sead::Vector3f& translate);

    const sead::Vector3f& getExtents() const;
    const sead::Vector3f& getTranslate() const;
    void getTransformedTranslate(sead::Vector3f* translate);

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    float getVolume() override;

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

    BoxShape* mShape;
};

}  // namespace ksys::phys
