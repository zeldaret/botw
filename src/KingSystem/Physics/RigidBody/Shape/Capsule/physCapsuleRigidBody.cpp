#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

CapsuleRigidBody* CapsuleRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createCapsule(param, heap);
}

CapsuleRigidBody::CapsuleRigidBody(hkpRigidBody* hk_body, CapsuleShape* shape,
                                   ContactLayerType layer_type, const sead::SafeString& name,
                                   bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

CapsuleRigidBody::~CapsuleRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        util::safeDelete(mShape);
    }
}

void CapsuleRigidBody::setRadius(float radius) {
    if (mShape->setRadius(radius))
        updateShape();
}

void CapsuleRigidBody::setVertices(const sead::Vector3f& va, const sead::Vector3f& vb) {
    if (mShape->setVertices(va, vb))
        updateShape();
}

float CapsuleRigidBody::getRadius() const {
    return mShape->getRadius();
}

void CapsuleRigidBody::getVertices(sead::Vector3f* va, sead::Vector3f* vb) const {
    mShape->getVertices(va, vb);
}

void CapsuleRigidBody::transformVertices(sead::Vector3f* va, sead::Vector3f* vb) {
    lock();
    const hkTransform& transform = getHkBody()->getMotion()->getTransform();
    mShape->transformVertices(va, vb, transform);
    unlock();
}

void CapsuleRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& CapsuleRigidBody::getMaterialMask() const {
    return mShape->material_mask;
}

float CapsuleRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* CapsuleRigidBody::getShape_() {
    return mShape;
}

const Shape* CapsuleRigidBody::getShape_() const {
    return mShape;
}

u32 CapsuleRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                        const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
