#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

CylinderShape* CylinderShape::make(const CylinderShapeParam& param, sead::Heap* heap) {
    void* storage = util::allocStorage<hkpCylinderShape>(heap);
    if (!storage)
        return nullptr;

    auto* hk_shape = new (storage)
        hkpCylinderShape(toHkVec4(param.vertex_a), toHkVec4(param.vertex_b), param.radius);

    return new (heap) CylinderShape(param, hk_shape);
}

CylinderShape::CylinderShape(const CylinderShapeParam& param, hkpCylinderShape* hk_shape)
    : mVertexA(param.vertex_a), mVertexB(param.vertex_b), mRadius(param.radius),
      mMaterialMask(param.common.getMaterialMask()), mHavokShape(hk_shape) {
    if (param.common.item_code_disable_stick)
        mMaterialMask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);

    setMaterialMask(mMaterialMask);
}

CylinderShape::~CylinderShape() {
    util::deallocateObjectUnsafe(mHavokShape);
}

void CylinderShape::setMaterialMask(const MaterialMask& mask) {
    mMaterialMask = mask;

    if (mHavokShape)
        mHavokShape->setUserData(mask.getRawData());
}

bool CylinderShape::setRadius(float radius) {
    if (mRadius == radius)
        return false;

    mRadius = radius;
    mFlags.set(Flag::Dirty);
    return true;
}

bool CylinderShape::setVertices(const sead::Vector3f& va, const sead::Vector3f& vb) {
    if (mVertexA == va && mVertexB == vb)
        return false;

    mVertexA = va;
    mVertexB = vb;
    mFlags.set(Flag::Dirty);
    return true;
}

CylinderShape* CylinderShape::clone(sead::Heap* heap) const {
    CylinderShapeParam param;
    param.radius = mRadius;
    param.vertex_a = mVertexA;
    param.vertex_b = mVertexB;
    auto* cloned = make(param, heap);
    cloned->setMaterialMask(mMaterialMask);
    return cloned;
}

float CylinderShape::getRadius() const {
    return mRadius;
}

void CylinderShape::getVertices(sead::Vector3f* va, sead::Vector3f* vb) {
    *va = mVertexA;
    *vb = mVertexB;
}

float CylinderShape::getVolume() const {
    const auto height = (mVertexA - mVertexB).length();
    return height * (sead::Mathf::pi() * mRadius * mRadius);
}

hkpShape* CylinderShape::getHavokShape() {
    return mHavokShape;
}

const hkpShape* CylinderShape::getHavokShape() const {
    return mHavokShape;
}

const hkpShape* CylinderShape::updateHavokShape() {
    if (!mFlags.isOn(Flag::Dirty))
        return nullptr;

    const auto ref_count = mHavokShape->getReferenceCount();
    mHavokShape =
        new (mHavokShape) hkpCylinderShape(toHkVec4(mVertexA), toHkVec4(mVertexB), mRadius);
    mHavokShape->setReferenceCount(ref_count);

    setMaterialMask(mMaterialMask);

    mFlags.reset(Flag::Dirty);
    return nullptr;
}

void CylinderShape::setScale(float scale) {
    setRadius(mRadius * scale);

    sead::Vector3f va, vb;
    getVertices(&va, &vb);
    setVertices(va * scale, vb * scale);
}

void CylinderShape::transformVertices(sead::Vector3f* va, sead::Vector3f* vb,
                                      const hkTransformf& transform) {
    hkVector4f vertex;

    vertex.setTransformedPos(transform, toHkVec4(mVertexA));
    storeToVec3(va, vertex);

    vertex.setTransformedPos(transform, toHkVec4(mVertexB));
    storeToVec3(vb, vertex);
}

}  // namespace ksys::phys
