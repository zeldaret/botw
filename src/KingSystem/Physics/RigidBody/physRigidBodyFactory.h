#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::phys {

class RigidBody;
struct RigidBodyParamView;

class RigidBodyFactory {
public:
    static RigidBody* createSphere(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createCapsule(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createCylinder(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createWaterCylinder(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createBox(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createWaterBox(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createPolytope(RigidBodyParamView* view, sead::Heap* heap);
    static RigidBody* createCollection(RigidBodyParamView* view, sead::Heap* heap);
};

}  // namespace ksys::phys
