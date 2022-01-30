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

    float getVolume() override;

protected:
    Shape* getShape_() override;
    const Shape* getShape_() const override;
    void m9() override;

    BoxShape* mShape;
};

}  // namespace ksys::phys
