#include "KingSystem/Physics/RigidBody/Shape/physBoxRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"

namespace ksys::phys {

BoxRigidBody* BoxRigidBody::make(RigidBodyInstanceParam* param, sead::Heap* heap) {
    return RigidBodyFactory::createBox(param, heap);
}

BoxRigidBody::BoxRigidBody(hkpRigidBody* hk_body, BoxShape* shape, ContactLayerType layer_type,
                           const sead::SafeString& name, bool set_flag_10, sead::Heap* heap)
    : RigidBodyFromShape(hk_body, layer_type, name, set_flag_10, heap), mShape(shape) {}

BoxRigidBody::~BoxRigidBody() {
    if (hasFlag(RigidBody::Flag::_10) && mShape) {
        delete mShape;
        mShape = nullptr;
    }
}

float BoxRigidBody::getVolume() {
    return mShape->getVolume();
}

Shape* BoxRigidBody::getShape_() {
    return mShape;
}

const Shape* BoxRigidBody::getShape_() const {
    return mShape;
}

}  // namespace ksys::phys
