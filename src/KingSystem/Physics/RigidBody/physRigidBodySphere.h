#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class SphereShape;

class SphereRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(SphereRigidBody, RigidBodyFromShape)
public:
    static SphereRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    SphereRigidBody(hkpRigidBody* hk_body, SphereShape* shape, ContactLayerType layer_type,
                    const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~SphereRigidBody() override;

    /// Set the sphere radius and trigger a shape update.
    void setRadius(float radius);
    /// Set the sphere translation and trigger a shape update.
    void setTranslate(const sead::Vector3f& translate);

    float getRadius() const;
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

private:
    SphereShape* mShape{};
};

}  // namespace ksys::phys
