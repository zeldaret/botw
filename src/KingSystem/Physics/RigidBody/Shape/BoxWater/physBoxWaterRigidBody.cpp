#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterShape.h"

namespace ksys::phys {

BoxWaterRigidBody* BoxWaterRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return createBoxWater(param, heap);
}

BoxWaterRigidBody::BoxWaterRigidBody(hkpRigidBody* hk_body, BoxWaterShape* shape,
                                     ContactLayerType layer_type, const sead::SafeString& name,
                                     bool unused, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, true, heap), mShape(shape) {}

BoxWaterRigidBody::~BoxWaterRigidBody() {
    delete mShape;
}

void BoxWaterRigidBody::setExtents(const sead::Vector3f& extents) {
    if (mShape->setExtents(extents))
        updateShape();
}

void BoxWaterRigidBody::setTranslate(const sead::Vector3f& translate) {
    if (mShape->setTranslate(translate))
        updateShape();
}

const sead::Vector3f& BoxWaterRigidBody::getExtents() const {
    return mShape->mExtents;
}

const sead::Vector3f& BoxWaterRigidBody::getTranslate() const {
    return mShape->mTranslate;
}

void BoxWaterRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& BoxWaterRigidBody::getMaterialMask() const {
    return mShape->mMaterialMask;
}

float BoxWaterRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* BoxWaterRigidBody::getShape_() {
    return mShape;
}

const Shape* BoxWaterRigidBody::getShape_() const {
    return mShape;
}

u32 BoxWaterRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                         const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
