#include "KingSystem/Physics/System/physEntityContactListener.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

EntityContactListener* EntityContactListener::make(ContactMgr* mgr, sead::Heap* heap) {
    auto* listener = new (heap) EntityContactListener(mgr, heap);
    listener->init(heap);
    return listener;
}

EntityContactListener::EntityContactListener(ContactMgr* mgr, sead::Heap* heap)
    : ContactListener(mgr, ContactLayerType::Entity, MaxNumLayersPerType) {}

EntityContactListener::~EntityContactListener() = default;

bool EntityContactListener::isObjectOrGroundOrNPCOrTree(const RigidBody& body) {
    switch (body.getContactLayer().value()) {
    case ContactLayer::EntityObject:
    case ContactLayer::EntityGroundObject:
    case ContactLayer::EntityNPC:
    case ContactLayer::EntityTree:
        if (body.hasFlag(RigidBody::Flag::_400000))
            break;
        return true;
    default:
        break;
    }
    return false;
}

bool EntityContactListener::isObjectOrGroundOrNPCOrTree(const hkpCdBody& cd_body) {
    auto* body = getRigidBody(*cd_body.getRootCollidable());
    if (!body)
        return false;

    return isObjectOrGroundOrNPCOrTree(*body);
}

void EntityContactListener::m11(const hkpContactPointEvent& event,
                                const RigidBodyCollisionMasks& masks_a,
                                const RigidBodyCollisionMasks& masks_b, RigidBody* body_a,
                                RigidBody* body_b) {
    auto* hk_point_properties = event.m_contactPointProperties;

    const MaterialMask mat_mask_a = MaterialMaskData(masks_a.material_mask);
    const MaterialMask mat_mask_b = MaterialMaskData(masks_b.material_mask);
    const auto* material_table = System::instance()->getMaterialTable();

    const auto mat_a = mat_mask_a.getMaterial();
    const auto mat_b = mat_mask_b.getMaterial();
    const auto properties = material_table->getPairProperties(mat_a, mat_b);

    const float friction = properties.friction *
                           sead::Mathf::min(body_a->getFrictionScale(), body_b->getFrictionScale());

    const float restitution =
        properties.restitution * sead::Mathf::min(body_a->getEffectiveRestitutionScale(),
                                                  body_b->getEffectiveRestitutionScale());

    hk_point_properties->setFriction(friction);
    hk_point_properties->setRestitution(restitution);
}

}  // namespace ksys::phys
