#pragma once

#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkpPlaneShape;

namespace ksys::phys {

struct BoxShapeParam;

class BoxWaterShape : public Shape {
    SEAD_RTTI_OVERRIDE(BoxWaterShape, Shape)
public:
    enum class Flag {
        IsWater = 1 << 0,
        Dirty = 1 << 1,
        /// Whether we have a transform (translation and/or rotation).
        HasTransform = 1 << 2,
    };

    static BoxWaterShape* make(const BoxShapeParam& param, sead::Heap* heap);
    BoxWaterShape* clone(sead::Heap* heap) const;

    BoxWaterShape(const BoxShapeParam& param, hkpPlaneShape* hk_shape);
    ~BoxWaterShape() override;

    void setMaterialMask(const MaterialMask& mask);
    bool setExtents(const sead::Vector3f& extents);
    bool setTranslate(const sead::Vector3f& translate);

    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;
    ShapeType getType() const override { return ShapeType::BoxWater; }

    bool hasNoTransform() const {
        return mTranslate == sead::Vector3f(0, 0, 0) && mRotate == sead::Vector3f(0, 0, 0);
    }

    sead::Vector3f mExtents;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Vector3f mTranslate;
    sead::Vector3f mRotate;
    hkpPlaneShape* mHavokShape{};
    MaterialMask mMaterialMask{};
};

}  // namespace ksys::phys
