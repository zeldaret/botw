#pragma once

#include <prim/seadDelegate.h>

class hkpContactPointEvent;

namespace ksys::phys {

class RigidBody;
struct RigidBodyCollisionMasks;

struct RigidBodyContactEvent {
    RigidBody* body;
    const RigidBodyCollisionMasks* collision_masks;
    const u32* shape_keys;
    const hkpContactPointEvent* event;
};

using RigidBodyContactCallback = sead::IDelegate1R<const RigidBodyContactEvent&, bool>;

}  // namespace ksys::phys
