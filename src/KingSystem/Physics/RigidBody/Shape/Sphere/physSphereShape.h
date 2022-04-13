#pragma once

#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

class hkpSphereShape;
class hkpConvexTranslateShape;
class hkTransformf;

namespace ksys::phys {

class SphereParam;

struct SphereShapeParam {
    sead::Vector3f translate = sead::Vector3f::zero;
    float radius = 1.0;
    CommonShapeParam common;
};

class SphereShape : public Shape {
    SEAD_RTTI_OVERRIDE(SphereShape, Shape)
public:
    enum class Flag {
        /// Whether there is a pending change.
        Dirty = 1 << 0,
        /// Whether we have a transform (translation and/or rotation).
        HasTransform = 1 << 1,
        /// Whether there is a pending transform change.
        DirtyTransform = 1 << 2,
    };

    static SphereShape* make(const SphereShapeParam& param, sead::Heap* heap);

    SphereShape(const SphereShapeParam& param, hkpSphereShape* shape,
                hkpConvexTranslateShape* translate_shape);
    ~SphereShape() override;

    SphereShape* clone(sead::Heap* heap) const;

    bool setTranslate(const sead::Vector3f& translate);
    bool setRadius(float radius);
    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const { return mMaterialMask; }

    ShapeType getType() const override { return ShapeType::Sphere; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;

    /// Get the transform's translation or mTranslate transformed by the matrix
    /// (if we have a non-zero translation vector).
    void getTranslate(sead::Vector3f* out, const hkTransformf& transform) const;

    float mRadius;
    hkpSphereShape* mHavokShape{};
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Vector3f mTranslate;
    MaterialMask mMaterialMask;
    hkpConvexTranslateShape* mTranslateShape{};
};

class SphereParam : public RigidBodyInstanceParam, public SphereShapeParam {
    SEAD_RTTI_OVERRIDE(SphereParam, RigidBodyInstanceParam)
public:
    SphereParam() : RigidBodyInstanceParam(ShapeType::Sphere) {}
};

}  // namespace ksys::phys
