#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <heap/seadHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

CapsuleShape::CapsuleShape(const CapsuleShapeParam& shape_, hkpShape* hkp_shape_)
    : vertex_a(shape_.vertex_a), vertex_b(shape_.vertex_b), radius(shape_.radius),
      material_mask(shape_.common.getMaterialMask()), shape(hkp_shape_) {
    if (shape_.common.item_code_disable_stick)
        material_mask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);
    setMaterialMask(material_mask);
}

void CapsuleShape::setMaterialMask(const MaterialMask& mask) {
    material_mask = mask;
    if (shape)
        shape->setUserData(mask.getRawData());
}

CapsuleShape* CapsuleShape::make(const CapsuleShapeParam& param, sead::Heap* heap) {
    void* ptr = util::allocStorage<hkpCapsuleShape>(heap);
    if (ptr == nullptr)
        return nullptr;

    auto* hk_shape =
        new (ptr) hkpCapsuleShape(toHkVec4(param.vertex_a), toHkVec4(param.vertex_b), param.radius);
    return new (heap) CapsuleShape(param, hk_shape);
}

CapsuleShape* CapsuleShape::clone(sead::Heap* heap) const {
    CapsuleShapeParam param_clone;
    param_clone.radius = radius;
    param_clone.vertex_a = vertex_a;
    param_clone.vertex_b = vertex_b;

    CapsuleShape* cloned = make(param_clone, heap);
    cloned->setMaterialMask(material_mask);
    return cloned;
}

f32 CapsuleShape::getRadius() const {
    return radius;
}

void CapsuleShape::getVertices(sead::Vector3f* va, sead::Vector3f* vb) const {
    if (va != nullptr)
        *va = vertex_a;
    if (vb != nullptr)
        *vb = vertex_b;
}

CapsuleShape::~CapsuleShape() {
    if (shape != nullptr) {
        ::operator delete(shape);
        shape = nullptr;
    }
}

bool CapsuleShape::setRadius(f32 r) {
    if (r == radius || r <= 0.0f) {
        return false;
    }
    radius = r;
    flags.set(Flag::Modified);
    return true;
}

bool CapsuleShape::setVertices(const sead::Vector3f& va, const sead::Vector3f& vb) {
    if (vertex_a == va && vertex_b == vb) {
        return false;
    }
    vertex_a = va;
    vertex_b = vb;
    flags.set(Flag::Modified);
    return true;
}

f32 CapsuleShape::getVolume() const {
    f32 dist = (vertex_a - vertex_b).length();
    return sead::Mathf::pi() * radius * radius * (dist + radius * 4.0f / 3.0f);
}

hkpShape* CapsuleShape::getHavokShape() {
    return shape;
}

const hkpShape* CapsuleShape::getHavokShape() const {
    return shape;
}

hkpShape* CapsuleShape::updateHavokShape() {
    if (!flags.isOn(Flag::Modified))
        return nullptr;

    const auto ref_count = shape->getReferenceCount();
    shape = new (shape) hkpCapsuleShape(toHkVec4(vertex_a), toHkVec4(vertex_b), radius);
    shape->setReferenceCount(ref_count);

    setMaterialMask(material_mask);

    flags.reset(Flag::Modified);
    return nullptr;
}

void CapsuleShape::setScale(float scale) {
    setRadius(radius * scale);

    sead::Vector3f va, vb;
    getVertices(&va, &vb);
    setVertices(va * scale, vb * scale);
}

void CapsuleShape::transformVertices(sead::Vector3f* veca, sead::Vector3f* vecb,
                                     const hkTransformf& rb_vec) {
    if (veca != nullptr) {
        hkVector4 tmp;
        tmp.setTransformedPos(rb_vec, toHkVec4(vertex_a));
        tmp.store<3>(veca->e.data());
    }
    if (vecb != nullptr) {
        hkVector4 tmp;
        tmp.setTransformedPos(rb_vec, toHkVec4(vertex_b));
        tmp.store<3>(vecb->e.data());
    }
}

}  // namespace ksys::phys
