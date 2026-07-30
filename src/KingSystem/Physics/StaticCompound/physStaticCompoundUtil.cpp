#include "KingSystem/Physics/StaticCompound/physStaticCompoundUtil.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Havok/Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h>
#include <Havok/Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

u32 getMaterialMaskFromCollidable(RigidBodyCollisionMasks* p_masks, u32* p_collision_filter_info,
                                  const hkpShape& shape, const u32* shape_key) {
    auto no_material = [&] {
        p_masks->material_mask = 0;
        *p_collision_filter_info = 0;
        return 1;
    };

    if (shape.getType() == hkcdShapeType::BV_COMPRESSED_MESH) {
        if (*shape_key == HK_INVALID_SHAPE_KEY)
            return no_material();

        const auto& mesh = static_cast<const hkpBvCompressedMeshShape&>(shape);
        if (mesh.getCollisionFilterInfoMode() ==
            hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_PALETTE) {
            *p_collision_filter_info = mesh.getCollisionFilterInfo(*shape_key);
        }

        if (mesh.getUserDataMode() != hkpBvCompressedMeshShape::PER_PRIMITIVE_DATA_NONE) {
            p_masks->material_mask = mesh.getPrimitiveUserData(*shape_key);
            return 0;
        }

        p_masks->material_mask = mesh.getUserData();
        return 0;
    }

    if (shape.getType() == hkcdShapeType::STATIC_COMPOUND) {
        if (*shape_key == HK_INVALID_SHAPE_KEY)
            return no_material();

        const auto& compound = static_cast<const hkpStaticCompoundShape&>(shape);
        int instance_id;
        hkpShapeKey child_key;
        compound.decomposeShapeKey(*shape_key, instance_id, child_key);
        const auto& instance = compound.getInstances()[instance_id];
        *p_collision_filter_info = compound.getCollisionFilterInfo(*shape_key);
        return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info, *instance.getShape(),
                                             &child_key);
    }

    if (shape.getType() == hkcdShapeType::LIST) {
        if (*shape_key == HK_INVALID_SHAPE_KEY)
            return no_material();

        hkpShapeBuffer buffer;
        const auto& list = static_cast<const hkpListShape&>(shape);
        return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info,
                                             *list.getChildShape(*shape_key, buffer), shape_key);
    }

    p_masks->material_mask = shape.getUserData();
    return 0;
}

void getBodyGroupAndObjectFromSCShape(StaticCompoundRigidBodyGroup** p_body_group,
                                      map::Object** p_object, const hkpShape& shape,
                                      const u32* shape_key) {
    if (shape.getType() != hkcdShapeType::STATIC_COMPOUND) {
        *p_body_group = nullptr;
        return;
    }

    auto* mgr = System::instance()->getStaticCompoundMgr();
    if (!mgr) {
        *p_body_group = nullptr;
        return;
    }

    mgr->getBodyGroupAndMapObject(p_body_group, p_object,
                                  static_cast<const hkpStaticCompoundShape&>(shape), shape_key);
}

u32 getCollisionFilterInfoFromCollidable(RigidBodyCollisionMasks* p_masks,
                                         u32* p_collision_filter_info,
                                         const hkpCollidable& collidable, const u32* shape_key) {
    *p_collision_filter_info = collidable.getCollisionFilterInfo();
    return getMaterialMaskFromCollidable(p_masks, p_collision_filter_info, *collidable.getShape(),
                                         shape_key);
}

}  // namespace ksys::phys
