#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"

#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physWaterCylinderShape.h"

namespace ksys::phys {

RigidBody* RigidBodyFactory::createSphere(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<SphereParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(1, *params, heap);
}

RigidBody* RigidBodyFactory::createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<CapsuleParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(1, *params, heap);
}

RigidBody* RigidBodyFactory::createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<CylinderParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(1, *params, heap);
}

RigidBody* RigidBodyFactory::createWaterCylinder(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<WaterCylinderParam>(params);
    auto* body = v->shape.createShape(heap);
    return body->createBody(1, *params, heap);
}

RigidBody* RigidBodyFactory::createBox(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<BoxParam>(params);
    auto* body = v->shape.createShape(heap);
    return body->createBody(1, *params, heap);
}

}  // namespace ksys::phys
