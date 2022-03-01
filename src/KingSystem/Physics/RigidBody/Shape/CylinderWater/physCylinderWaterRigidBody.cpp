#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterShape.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::phys {

CylinderWaterRigidBody* CylinderWaterRigidBody::make(RigidBodyInstanceParam* param,
                                                     sead::Heap* heap) {
    return createCylinderWater(param, heap);
}

CylinderWaterRigidBody::CylinderWaterRigidBody(hkpRigidBody* hk_body, CylinderWaterShape* shape,
                                               ContactLayerType layer_type,
                                               const sead::SafeString& name, bool set_flag_10,
                                               sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

CylinderWaterRigidBody::~CylinderWaterRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape)
        util::safeDelete(mShape);
}

void CylinderWaterRigidBody::setRadius(float radius) {
    if (mShape->setRadius(radius))
        updateShape();
}

void CylinderWaterRigidBody::setHeight(float height) {
    if (mShape->setHeight(height))
        updateShape();
}

float CylinderWaterRigidBody::getRadius() const {
    return mShape->getRadius();
}

float CylinderWaterRigidBody::getHeight() const {
    return mShape->getHeight();
}

void CylinderWaterRigidBody::setMaterialMask(const MaterialMask& mask) {
    mShape->setMaterialMask(mask);
}

const MaterialMask& CylinderWaterRigidBody::getMaterialMask() const {
    return mShape->getMaterialMask();
}

float CylinderWaterRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* CylinderWaterRigidBody::getShape_() {
    return mShape;
}

const Shape* CylinderWaterRigidBody::getShape_() const {
    return mShape;
}

u32 CylinderWaterRigidBody::getCollisionMasks(RigidBody::CollisionMasks* masks, const u32* unk,
                                              const sead::Vector3f& contact_point) {
    masks->ignored_layers = ~mContactMask.getDirect();
    masks->collision_filter_info = getCollisionFilterInfo();
    masks->material_mask = getMaterialMask().getRawData();
    return 0;
}

}  // namespace ksys::phys
