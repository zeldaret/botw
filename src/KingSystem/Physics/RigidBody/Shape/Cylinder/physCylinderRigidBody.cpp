#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

CylinderRigidBody* CylinderRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createCylinder(param, heap);
}

CylinderRigidBody::CylinderRigidBody(hkpRigidBody* hk_body, CylinderShape* shape,
                                     ContactLayerType layer_type, const sead::SafeString& name,
                                     bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

CylinderRigidBody::~CylinderRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape)
        util::safeDelete(mShape);
}

void CylinderRigidBody::setRadius(float radius) {
    if (mShape->setRadius(radius))
        updateShape();
}

void CylinderRigidBody::setVertices(const sead::Vector3f& va, const sead::Vector3f& vb) {
    if (mShape->setVertices(va, vb))
        updateShape();
}

float CylinderRigidBody::getRadius() const {
    return mShape->getRadius();
}

void CylinderRigidBody::getVertices(sead::Vector3f* va, sead::Vector3f* vb) const {
    mShape->getVertices(va, vb);
}

void CylinderRigidBody::transformVertices(sead::Vector3f* va, sead::Vector3f* vb) {
    lock();
    const hkTransform& transform = getHkBody()->getMotion()->getTransform();
    unlock();
    mShape->transformVertices(va, vb, transform);
}

void CylinderRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& CylinderRigidBody::getMaterialMask() const {
    return mShape->getMaterialMask();
}

float CylinderRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* CylinderRigidBody::getShape_() {
    return mShape;
}

const Shape* CylinderRigidBody::getShape_() const {
    return mShape;
}

u32 CylinderRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                         const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
