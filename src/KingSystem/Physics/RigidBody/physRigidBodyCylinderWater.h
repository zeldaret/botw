#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

class CylinderWaterShape;

class CylinderWaterRigidBody : public RigidBodyFromShape {
    SEAD_RTTI_OVERRIDE(CylinderWaterRigidBody, RigidBodyFromShape)
public:
    static CylinderWaterRigidBody* make(RigidBodyInstanceParam* param, sead::Heap* heap);

    CylinderWaterRigidBody(hkpRigidBody* hk_body, CylinderWaterShape* shape,
                           ContactLayerType layer_type, const sead::SafeString& name,
                           bool set_flag_10, sead::Heap* heap);
    ~CylinderWaterRigidBody() override;

    void setRadius(float radius);
    void setHeight(float height);

    float getRadius() const;
    float getHeight() const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const;

    float getVolume() override;

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    u32 getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                          const sead::Vector3f& contact_point) override;

private:
    CylinderWaterShape* mShape{};
    float _d8 = 1.0;
};

}  // namespace ksys::phys
