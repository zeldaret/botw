#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <heap/seadHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

CapsuleShape::CapsuleShape(const CapsuleShapeParam& shape_, hkpShape* hkp_shape_)
    : vertex_a(shape_.vertex_a), vertex_b(shape_.vertex_b), radius(shape_.radius),
      material_mask(shape_.common.material, shape_.common.sub_material, shape_.common.floor_code,
                    shape_.common.wall_code),
      shape(hkp_shape_) {
    if (shape_.common.item_code_disable_stick)
        material_mask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);
    setMaterialMask(material_mask);
}

void CapsuleShape::setMaterialMask(const MaterialMask& mask) {
    material_mask = mask;
    if (shape)
        shape->setUserData(mask.getRawData());
}

CapsuleShape* CapsuleShapeParam::createShape(sead::Heap* heap) {
    void* ptr = heap->tryAlloc(sizeof(hkpCapsuleShape), 0x10);
    if (ptr == nullptr)
        return nullptr;

    auto* hk_shape =
        new (ptr) hkpCapsuleShape(hkVector4(vertex_a.x, vertex_a.y, vertex_a.z),
                                  hkVector4(vertex_b.x, vertex_b.y, vertex_b.z), radius);
    return new (heap) CapsuleShape(*this, hk_shape);
}

CapsuleShape* CapsuleShape::clone(sead::Heap* heap) {
    CapsuleShapeParam param_clone;
    param_clone.radius = radius;
    param_clone.vertex_a = vertex_a;
    param_clone.vertex_b = vertex_b;

    CapsuleShape* cloned = param_clone.createShape(heap);
    cloned->material_mask = material_mask;
    if (cloned->shape != nullptr)
        cloned->shape->setUserData(material_mask.getRawData());
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

void CapsuleShape::sub_7100FABE80(sead::Vector3f* veca, sead::Vector3f* vecb,
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
