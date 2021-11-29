#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"

#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physWaterCylinderShape.h"

namespace ksys::phys {

RigidBody* RigidBodyFactory::createSphere(RigidBodyParamView* view, sead::Heap* heap) {
    if (isSensorLayer(view->contact_layer) == 1 && view->motion_type == MotionType::Dynamic)
        view->motion_type = MotionType::Keyframed;

    SphereView* v = sead::DynamicCast<SphereView>(view);
    SphereBody* body = v->shape.init(heap);
    return body->init(1, view, heap);
}

RigidBody* RigidBodyFactory::createCapsule(RigidBodyParamView* view, sead::Heap* heap) {
    if (isSensorLayer(view->contact_layer) == 1 && view->motion_type == MotionType::Dynamic)
        view->motion_type = MotionType::Keyframed;

    CapsuleView* v = sead::DynamicCast<CapsuleView>(view);
    CapsuleBody* body = v->shape.init(heap);
    return body->init(1, view, heap);
}

RigidBody* RigidBodyFactory::createCylinder(RigidBodyParamView* view, sead::Heap* heap) {
    if (isSensorLayer(view->contact_layer) == 1 && view->motion_type == MotionType::Dynamic)
        view->motion_type = MotionType::Keyframed;

    CylinderView* v = sead::DynamicCast<CylinderView>(view);
    CylinderBody* body = v->shape.init(heap);
    return body->init(1, view, heap);
}

RigidBody* RigidBodyFactory::createWaterCylinder(RigidBodyParamView* view, sead::Heap* heap) {
    if (isSensorLayer(view->contact_layer) == 1 && view->motion_type == MotionType::Dynamic)
        view->motion_type = MotionType::Keyframed;

    WaterCylinderView* v = sead::DynamicCast<WaterCylinderView>(view);
    WaterCylinderBody* body = v->shape.init(heap);
    return body->init(1, view, heap);
}

RigidBody* RigidBodyFactory::createBox(RigidBodyParamView* view, sead::Heap* heap) {
    if (isSensorLayer(view->contact_layer) == 1 && view->motion_type == MotionType::Dynamic)
        view->motion_type = MotionType::Keyframed;

    BoxView* v = sead::DynamicCast<BoxView>(view);
    BoxBody* body = v->shape.init(heap);
    return body->init(1, view, heap);
}

}  // namespace ksys::phys
