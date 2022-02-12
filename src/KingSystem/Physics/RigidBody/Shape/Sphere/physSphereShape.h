#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

namespace ksys::phys {

class SphereParam;

struct SphereShapeParam {
    sead::Vector3f translate;
    float radius;
    CommonShapeParam common;
};

class SphereShape : public Shape {
    SEAD_RTTI_OVERRIDE(SphereShape, Shape)
public:
    static SphereShape* make(const SphereShapeParam& param, sead::Heap* heap);
    SphereShape* clone(sead::Heap* heap) const;

    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const { return mMaterialMask; }

private:
    char _8[0x28 - 0x8];
    MaterialMask mMaterialMask;
};

class SphereParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(SphereParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    SphereShapeParam shape;
};

}  // namespace ksys::phys
