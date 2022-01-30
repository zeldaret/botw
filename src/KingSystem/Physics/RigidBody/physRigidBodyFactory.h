#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::phys {

class BoxRigidBody;
class RigidBody;
struct RigidBodyInstanceParam;

class RigidBodyFactory {
public:
    static RigidBody* createSphere(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCylinderWater(RigidBodyInstanceParam* params, sead::Heap* heap);
    static BoxRigidBody* createBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createWaterBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createPolytope(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCollection(RigidBodyInstanceParam* params, sead::Heap* heap);
};

}  // namespace ksys::phys
