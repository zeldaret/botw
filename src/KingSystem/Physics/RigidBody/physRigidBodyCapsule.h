#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

struct CapsuleShape;

class CapsuleRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(CapsuleRigidBody, RigidBodyFromShape)
public:
    static CapsuleRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    CapsuleRigidBody(hkpRigidBody* hk_body, CapsuleShape* shape, ContactLayerType layer_type,
                     const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~CapsuleRigidBody() override;

    void setRadius(float radius);
    void setVertices(const sead::Vector3f& va, const sead::Vector3f& vb);

    float getRadius() const;
    void getVertices(sead::Vector3f* va, sead::Vector3f* vb) const;
    void transformVertices(sead::Vector3f* va, sead::Vector3f* vb);

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    float getVolume() override;

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

    CapsuleShape* mShape{};
};

}  // namespace ksys::phys
