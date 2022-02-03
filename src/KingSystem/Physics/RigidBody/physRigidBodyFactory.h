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
class RigidBody;
struct RigidBodyInstanceParam;

class RigidBodyFactory {
public:
    static RigidBody* createSphere(RigidBodyInstanceParam* params, sead::Heap* heap);
    static CapsuleRigidBody* createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap);
    static CylinderRigidBody* createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCylinderWater(RigidBodyInstanceParam* params, sead::Heap* heap);
    static BoxRigidBody* createBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static BoxWaterRigidBody* createBoxWater(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createPolytope(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCollection(RigidBodyInstanceParam* params, sead::Heap* heap);
};

}  // namespace ksys::phys
