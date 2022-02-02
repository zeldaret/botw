#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physBoxWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

template <typename RigidBodyType, typename ShapeType, typename ParamType>
static RigidBodyType* createRigidBody(RigidBodyInstanceParam* param, sead::Heap* heap) {
    if (param->isDynamicSensor())
        param->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<ParamType>(param);
    auto* shape = ShapeType::make(v->shape, heap);
    return RigidBodyFromShape::make<RigidBodyType, ShapeType>(*shape, true, *param, heap);
}

RigidBody* RigidBodyFactory::createSphere(RigidBodyInstanceParam* params, sead::Heap* heap) {
    if (params->isDynamicSensor())
        params->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<SphereParam>(params);
    auto* shape = v->shape.createShape(heap);
    return shape->createBody(true, *params, heap);
}

CapsuleRigidBody* RigidBodyFactory::createCapsule(RigidBodyInstanceParam* params,
                                                  sead::Heap* heap) {
    return createRigidBody<CapsuleRigidBody, CapsuleShape, CapsuleParam>(params, heap);
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

BoxRigidBody* RigidBodyFactory::createBox(RigidBodyInstanceParam* params, sead::Heap* heap) {
    return createRigidBody<BoxRigidBody, BoxShape, BoxParam>(params, heap);
}

BoxWaterRigidBody* RigidBodyFactory::createBoxWater(RigidBodyInstanceParam* params,
                                                    sead::Heap* heap) {
    return createRigidBody<BoxWaterRigidBody, BoxWaterShape, BoxParam>(params, heap);
}

}  // namespace ksys::phys
