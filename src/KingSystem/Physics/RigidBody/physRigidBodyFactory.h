#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::phys {

class RigidBody;
struct RigidBodyInstanceParam;

class RigidBodyFactory {
public:
    static RigidBody* createSphere(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCapsule(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCylinder(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createWaterCylinder(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createWaterBox(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createPolytope(RigidBodyInstanceParam* params, sead::Heap* heap);
    static RigidBody* createCollection(RigidBodyInstanceParam* params, sead::Heap* heap);
};

}  // namespace ksys::phys
