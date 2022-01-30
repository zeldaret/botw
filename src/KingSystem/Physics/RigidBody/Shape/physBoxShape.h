#pragma once

#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/System/physMaterialMask.h"

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

    BoxShape(const BoxShapeParam& param, hkpBoxShape* shape,
             hkpConvexTransformShape* transform_shape);
    ~BoxShape() override;

    BoxRigidBody* createBody(bool flag, const RigidBodyInstanceParam& params, sead::Heap* heap);

    bool setExtents(const sead::Vector3f& extents);
    bool setTranslate(const sead::Vector3f& translate);
    void setMaterialMask(const MaterialMask& mask);

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
    BoxShape* createShape(sead::Heap* heap);

    sead::Vector3f extents;
    sead::Vector3f translate;
    sead::Vector3f rotate;
    float convex_radius;
    CommonShapeParam common;
};

class BoxParam : public RigidBodyInstanceParam {
    SEAD_RTTI_OVERRIDE(BoxParam, RigidBodyInstanceParam)
public:
    u8 _90;
    float _94;
    BoxShapeParam shape;
};

}  // namespace ksys::phys
