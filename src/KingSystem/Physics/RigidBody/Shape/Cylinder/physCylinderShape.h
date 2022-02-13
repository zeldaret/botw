#pragma once

#include <math/seadVector.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkTransformf;
class hkpCylinderShape;

namespace ksys::phys {

class CylinderParam;
struct CylinderShapeParam;

class CylinderShape : public Shape {
    SEAD_RTTI_OVERRIDE(CylinderShape, Shape)
public:
    enum class Flag {
        Dirty = 1 << 0,
    };

    static CylinderShape* make(const CylinderShapeParam& param, sead::Heap* heap);

    CylinderShape(const CylinderShapeParam& param, hkpCylinderShape* hk_shape);
    ~CylinderShape() override;

    const MaterialMask& getMaterialMask() const { return mMaterialMask; }
    void setMaterialMask(const MaterialMask& mask);

    float getRadius() const;
    bool setRadius(float radius);

    void getVertices(sead::Vector3f* va, sead::Vector3f* vb);
    bool setVertices(const sead::Vector3f& va, const sead::Vector3f& vb);

    CylinderShape* clone(sead::Heap* heap) const;

    ShapeType getType() const override { return ShapeType::Cylinder; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;

    void transformVertices(sead::Vector3f* va, sead::Vector3f* vb, const hkTransformf& transform);

private:
    sead::Vector3f mVertexA;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags;
    sead::Vector3f mVertexB;
    float mRadius;
    MaterialMask mMaterialMask;
    hkpCylinderShape* mHavokShape;
};

struct CylinderShapeParam {
    /// The center of the first circular base.
    sead::Vector3f vertex_a = -1 * sead::Vector3f::ey;
    /// The radius of the circular bases.
    float radius = 1.0;
    /// The center of the second circular base.
    sead::Vector3f vertex_b = +1 * sead::Vector3f::ey;
    /// Additional shell radius around the cylinder.
    /// @warning This is ignored by CylinderShape.
    float convex_radius = 0.05;
    CommonShapeParam common;
};

class CylinderParam : public RigidBodyInstanceParam, public CylinderShapeParam {
    SEAD_RTTI_OVERRIDE(CylinderParam, RigidBodyInstanceParam)
public:
    CylinderParam() : RigidBodyInstanceParam(ShapeType::Cylinder) {}
};

}  // namespace ksys::phys
