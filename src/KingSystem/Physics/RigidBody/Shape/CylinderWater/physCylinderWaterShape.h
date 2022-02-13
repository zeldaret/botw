#pragma once

#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

class HavokCylinderWaterShape;

class CylinderWaterShape : public Shape {
    SEAD_RTTI_OVERRIDE(CylinderWaterShape, Shape)
public:
    enum class Flag {
        Dirty = 1 << 0,
    };

    static CylinderWaterShape* make(const CylinderShapeParam& param, sead::Heap* heap);

    CylinderWaterShape(const CylinderShapeParam& param, HavokCylinderWaterShape* shape);
    ~CylinderWaterShape() override;

    void setMaterialMask(const MaterialMask& mask);
    bool setRadius(float radius);
    bool setHeight(float height);

    CylinderWaterShape* clone(sead::Heap* heap) const;

    const MaterialMask& getMaterialMask() const { return mMaterialMask; }
    float getRadius() const;
    float getHeight() const;

    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;
    ShapeType getType() const override { return ShapeType::CylinderWater; }

private:
    MaterialMask mMaterialMask;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    HavokCylinderWaterShape* mHavokShape;
};

}  // namespace ksys::phys
