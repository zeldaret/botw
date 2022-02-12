#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::phys {

class BoxRigidBody;
class BoxWaterRigidBody;
class CapsuleRigidBody;
class CylinderRigidBody;
class CylinderWaterRigidBody;
class ListShapeRigidBody;
class PolytopeRigidBody;
class RigidBody;
struct RigidBodyInstanceParam;
class SphereRigidBody;

class RigidBodyFactory {
public:
    static SphereRigidBody* createSphere(RigidBodyInstanceParam* params, sead::Heap* heap);
    static CapsuleRigidBody* createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap);
    static CylinderRigidBody* createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap);
    static CylinderWaterRigidBody* createCylinderWater(RigidBodyInstanceParam* params,
                                                       sead::Heap* heap);
    static BoxRigidBody* createBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static BoxWaterRigidBody* createBoxWater(RigidBodyInstanceParam* params, sead::Heap* heap);
    static PolytopeRigidBody* createPolytope(RigidBodyInstanceParam* params, sead::Heap* heap);
    static ListShapeRigidBody* createList(RigidBodyInstanceParam* params, sead::Heap* heap);
};

}  // namespace ksys::phys
