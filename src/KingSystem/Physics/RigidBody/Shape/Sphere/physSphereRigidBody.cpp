#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"

namespace ksys::phys {

SphereRigidBody* SphereRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createSphere(param, heap);
}

SphereRigidBody::SphereRigidBody(hkpRigidBody* hk_body, SphereShape* shape,
                                 ContactLayerType layer_type, const sead::SafeString& name,
                                 bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

SphereRigidBody::~SphereRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        delete mShape;
        mShape = nullptr;
    }
}

void SphereRigidBody::setRadius(float radius) {
    if (mShape->setRadius(radius))
        updateShape();
}

void SphereRigidBody::setTranslate(const sead::Vector3f& translate) {
    if (mShape->setTranslate(translate))
        updateShape();
}

float SphereRigidBody::getRadius() const {
    return mShape->mRadius;
}

const sead::Vector3f& SphereRigidBody::getTranslate() const {
    return mShape->mTranslate;
}

void SphereRigidBody::getTransformedTranslate(sead::Vector3f* translate) {
    lock();
    const auto& transform = getHkBody()->getMotion()->getMotionState()->getTransform();
    unlock();
    mShape->getTranslate(translate, transform);
}

void SphereRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& SphereRigidBody::getMaterialMask() const {
    return mShape->mMaterialMask;
}

float SphereRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* SphereRigidBody::getShape_() {
    return mShape;
}

const Shape* SphereRigidBody::getShape_() const {
    return mShape;
}

u32 SphereRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                       const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
