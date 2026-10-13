#pragma once

#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkTransformf;
class hkpBoxShape;
class hkpConvexTransformShape;

namespace ksys::phys {

class BoxParam;
class BoxRigidBody;
struct BoxShapeParam;

class BoxShape : public Shape {
    SEAD_RTTI_OVERRIDE(BoxShape, Shape)
public:
    enum class Flag {
        /// Whether there is a pending change.
        Dirty = 1 << 0,
        /// Whether we have a transform (translation and/or rotation).
        HasTransform = 1 << 1,
        /// Whether there is a pending transform change.
        DirtyTransform = 1 << 2,
    };

    static BoxShape* make(const BoxShapeParam& param, sead::Heap* heap);

    BoxShape(const BoxShapeParam& param, hkpBoxShape* shape,
             hkpConvexTransformShape* transform_shape);
    ~BoxShape() override;

    BoxShape* clone(sead::Heap* heap) const;
    BoxRigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);

    bool setExtents(const sead::Vector3f& extents);
    bool setTranslate(const sead::Vector3f& translate);
    void setMaterialMask(const MaterialMask& mask);
    const MaterialMask& getMaterialMask() const { return mMaterialMask; }

    ShapeType getType() const override { return ShapeType::Box; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;

    /// Get the transform's translation or mTranslate transformed by the matrix
    /// (if we have a non-zero translation vector).
    void getTranslate(sead::Vector3f* out, const hkTransformf& transform) const;

    sead::Vector3f mExtents;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Vector3f mTranslate;
    sead::Vector3f mRotate;
    hkpBoxShape* mHavokShape{};
    MaterialMask mMaterialMask{};
    hkpConvexTransformShape* mTransformShape{};
};

struct BoxShapeParam {
    sead::Vector3f extents = {0.5, 0.5, 0.5};
    sead::Vector3f translate = sead::Vector3f::zero;
    sead::Vector3f rotate = sead::Vector3f::zero;
    float convex_radius = 0.05;
    CommonShapeParam common;
};

class BoxParam : public RigidBodyInstanceParam, public BoxShapeParam {
    SEAD_RTTI_OVERRIDE(BoxParam, RigidBodyInstanceParam)
public:
    BoxParam() : RigidBodyInstanceParam(ShapeType::Box) {}
};

}  // namespace ksys::phys
