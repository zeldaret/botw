#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

class hkpCollidable;
class hkpShape;

namespace ksys::map {
class Object;
}

namespace ksys::phys {

class StaticCompoundRigidBodyGroup;
struct RigidBodyCollisionMasks;

// 0x0000007100fd0810
u32 getMaterialMaskFromShape(const hkpShape& shape, const u32* shape_key,
                             const sead::Vector3f& position);

// 0x0000007100fd086c
bool getMaterialMaskFromCollidable(RigidBodyCollisionMasks* p_masks, u32* p_collision_filter_info,
                                   const hkpShape& shape, const u32* shape_key);

// 0x0000007100fd09d0
void getBodyGroupAndObjectFromSCShape(StaticCompoundRigidBodyGroup** p_body_group,
                                      map::Object** p_object, const hkpShape& shape,
                                      const u32* shape_key);

// 0x0000007100fd0a1c
u32 getCollisionFilterInfoFromCollidable(RigidBodyCollisionMasks* p_masks,
                                         u32* p_collision_filter_info,
                                         const hkpCollidable& collidable, const u32* shape_key);

}  // namespace ksys::phys
