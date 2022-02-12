#include "KingSystem/Physics/RigidBody/physRigidBodyFactory.h"
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterRigidBody.h"
#include "KingSystem/Physics/RigidBody/Shape/CylinderWater/physCylinderWaterShape.h"
#include "KingSystem/Physics/RigidBody/Shape/List/physListShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"

namespace ksys::phys {

template <typename RigidBodyType, typename ShapeType, typename ParamType>
static RigidBodyType* createRigidBody(RigidBodyInstanceParam* param, sead::Heap* heap) {
    if (param->isDynamicSensor())
        param->motion_type = MotionType::Keyframed;

    auto* v = sead::DynamicCast<ParamType>(param);
    auto* shape = ShapeType::make(v->shape, heap);
    return RigidBodyFromShape::make<RigidBodyType, ShapeType>(shape, true, *param, heap);
}

SphereRigidBody* RigidBodyFactory::createSphere(RigidBodyInstanceParam* params, sead::Heap* heap) {
    return createRigidBody<SphereRigidBody, SphereShape, SphereParam>(params, heap);
}

CapsuleRigidBody* RigidBodyFactory::createCapsule(RigidBodyInstanceParam* params,
                                                  sead::Heap* heap) {
    return createRigidBody<CapsuleRigidBody, CapsuleShape, CapsuleParam>(params, heap);
}

CylinderRigidBody* RigidBodyFactory::createCylinder(RigidBodyInstanceParam* params,
                                                    sead::Heap* heap) {
    return createRigidBody<CylinderRigidBody, CylinderShape, CylinderParam>(params, heap);
}

CylinderWaterRigidBody* RigidBodyFactory::createCylinderWater(RigidBodyInstanceParam* params,
                                                              sead::Heap* heap) {
    return createRigidBody<CylinderWaterRigidBody, CylinderWaterShape, CylinderParam>(params, heap);
}

BoxRigidBody* RigidBodyFactory::createBox(RigidBodyInstanceParam* params, sead::Heap* heap) {
    return createRigidBody<BoxRigidBody, BoxShape, BoxParam>(params, heap);
}

BoxWaterRigidBody* RigidBodyFactory::createBoxWater(RigidBodyInstanceParam* params,
                                                    sead::Heap* heap) {
    return createRigidBody<BoxWaterRigidBody, BoxWaterShape, BoxParam>(params, heap);
}

PolytopeRigidBody* RigidBodyFactory::createPolytope(RigidBodyInstanceParam* params,
                                                    sead::Heap* heap) {
    return createRigidBody<PolytopeRigidBody, PolytopeShape, PolytopeParam>(params, heap);
}

ListShapeRigidBody* RigidBodyFactory::createList(RigidBodyInstanceParam* params, sead::Heap* heap) {
    return createRigidBody<ListShapeRigidBody, ListShape, ListShapeRigidBodyParam>(params, heap);
}

}  // namespace ksys::phys
