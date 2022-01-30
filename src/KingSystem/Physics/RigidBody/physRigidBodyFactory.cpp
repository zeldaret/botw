#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"

#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"

namespace ksys::phys {

RigidBody* RigidBodyFactory::createSphere(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<SphereParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

RigidBody* RigidBodyFactory::createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<CapsuleParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

RigidBody* RigidBodyFactory::createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<CylinderParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

RigidBody* RigidBodyFactory::createCylinderWater(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<CylinderWaterParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

RigidBody* RigidBodyFactory::createBox(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<BoxParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

}  // namespace ksys::phys
