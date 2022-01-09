#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <heap/seadHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

CapsuleBody::CapsuleBody(const CapsuleShape& shape_, hkpShape* hkp_shape_)
    : vertex_a(shape_.vertex_a), vertex_b(shape_.vertex_b), radius(shape_.radius),
      material_mask(shape_.material, shape_.sub_material, shape_.floor_code, shape_.wall_code),
      shape(hkp_shape_) {
    if (shape_._38)
        material_mask.getData().setCustomFlag(MaterialMaskData::CustomFlag::_0);
    setMaterialMask(material_mask);
}

void CapsuleBody::setMaterialMask(const MaterialMask& mask) {
    material_mask = mask;
    if (shape)
        shape->setUserData(mask.getRawData());
}

CapsuleBody* CapsuleShape::init(sead::Heap* heap) {
    void* ptr = heap->tryAlloc(sizeof(hkpCapsuleShape), 0x10);
    if (ptr == nullptr)
        return nullptr;

    auto* hk_shape =
        new (ptr) hkpCapsuleShape(hkVector4(vertex_a.x, vertex_a.y, vertex_a.z),
                                  hkVector4(vertex_b.x, vertex_b.y, vertex_b.z), radius);
    return new (heap) CapsuleBody(*this, hk_shape);
}

CapsuleBody* CapsuleBody::clone(sead::Heap* heap) {
    CapsuleShape shape;
    shape.radius = radius;
    shape.vertex_a = vertex_a;
    shape.vertex_b = vertex_b;

    CapsuleBody* body = shape.init(heap);
    body->material_mask = material_mask;
    if (body->shape != nullptr)
        body->shape->setUserData(material_mask.getRawData());
    return body;
}

f32 CapsuleBody::getRadius() const {
    return radius;
}

void CapsuleBody::getVertices(sead::Vector3f* va, sead::Vector3f* vb) const {
    if (va != nullptr)
        *va = vertex_a;
    if (vb != nullptr)
        *vb = vertex_b;
}

CapsuleBody::~CapsuleBody() {
    if (shape != nullptr) {
        ::operator delete(shape);
        shape = nullptr;
    }
}

bool CapsuleBody::setRadius(f32 r) {
    if (r == radius || r <= 0.0f) {
        return false;
    }
    radius = r;
    flags.set(Flag::Modified);
    return true;
}

bool CapsuleBody::setVertices(const sead::Vector3f& va, const sead::Vector3f& vb) {
    if (vertex_a == va && vertex_b == vb) {
        return false;
    }
    vertex_a = va;
    vertex_b = vb;
    flags.set(Flag::Modified);
    return true;
}

f32 CapsuleBody::getVolume() const {
    f32 dist = (vertex_a - vertex_b).length();
    return sead::Mathf::pi() * radius * radius * (dist + radius * 4.0f / 3.0f);
}

hkpShape* CapsuleBody::getShape() {
    return shape;
}

const hkpShape* CapsuleBody::getShape() const {
    return shape;
}

void CapsuleBody::sub_7100FABE80(sead::Vector3f* veca, sead::Vector3f* vecb,
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
