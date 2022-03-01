#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class CylinderShape;

class CylinderRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(CylinderRigidBody, RigidBodyFromShape)
public:
    static CylinderRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    CylinderRigidBody(hkpRigidBody* hk_body, CylinderShape* shape, ContactLayerType layer_type,
                      const sead::SafeString& name, bool set_flag_10, sead::Heap* heap);
    ~CylinderRigidBody() override;

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

private:
    CylinderShape* mShape;
};

}  // namespace ksys::phys
