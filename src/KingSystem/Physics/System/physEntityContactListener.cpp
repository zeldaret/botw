#include "KingSystem/Physics/System/physEntityContactListener.h"
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCdBody.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpResponseModifier.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Havok/Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.h>
#include <Havok/Physics2012/Dynamics/World/hkpSimulationIsland.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/TerrainHeightField/physTerrainHeightFieldRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyMotionEntity.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

using ContactFlag = RigidBodyMotionEntity::ContactFlag;

static bool shouldProcessEntityContact(sead::BitFlag32 ignored_layers_a,
                                       sead::BitFlag32 ignored_layers_b, ContactLayer layer_a,
                                       ContactLayer layer_b) {
    auto* filter = System::instance()->getGroupFilter(ContactLayerType::Entity);
    return filter->shouldContactNeverBeIgnored(layer_a, layer_b) ||
           ignored_layers_a.isOffBit(layer_b) || ignored_layers_b.isOffBit(layer_a);
}

static bool shouldProcessEntityContact(u32 ignored_layers_a, u32 ignored_layers_b,
                                       ContactLayer layer_a, ContactLayer layer_b) {
    return shouldProcessEntityContact(sead::BitFlag32(ignored_layers_a),
                                      sead::BitFlag32(ignored_layers_b), layer_a, layer_b);
}

static bool shouldProcessEntityContact(const RigidBody* body_a, const RigidBody* body_b) {
    const auto ignored_layers_a = body_a->getIgnoredLayers();
    const auto ignored_layers_b = body_b->getIgnoredLayers();

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    return shouldProcessEntityContact(ignored_layers_a, ignored_layers_b, layer_a, layer_b);
}

// TODO: rename
static bool hasEntityWithMotionFlag80(const hkpCollisionEvent& event) {
    bool has_flag_80 = false;
    auto* island = event.getSimulationIsland();
    for (int i = 0; i < island->getEntities().getSize(); ++i) {
        auto* entity = getHkpEntity(*island->getEntities()[i]->getCollidable());
        if (!entity)
            continue;

        bool on = getRigidBody(*entity)->isEntityMotionFlag80On();
        has_flag_80 |= on;
        if (on)
            break;
    }
    return has_flag_80;
}

EntityContactListener* EntityContactListener::make(ContactMgr* mgr, sead::Heap* heap) {
    auto* listener = new (heap) EntityContactListener(mgr, heap);
    listener->init(heap);
    return listener;
}

EntityContactListener::EntityContactListener(ContactMgr* mgr, sead::Heap* heap)
    : ContactListener(mgr, ContactLayerType::Entity, MaxNumLayersPerType) {}

EntityContactListener::~EntityContactListener() = default;

void EntityContactListener::collisionAddedCallback(const hkpCollisionEvent& event) {
    auto* body_a = getRigidBody(*event.getBody(0));
    auto* body_b = getRigidBody(*event.getBody(1));

    handleCollisionAdded(event, body_a, body_b);

    const auto ignored_layers_a = body_a->getIgnoredLayers();
    const auto ignored_layers_b = body_b->getIgnoredLayers();

    const auto layer_a = body_a->getContactLayer();
    const auto layer_b = body_b->getContactLayer();

    bool should_process =
        shouldProcessEntityContact(ignored_layers_a, ignored_layers_b, layer_a, layer_b);
    if (!should_process) {
        setMagneMassScalingForContactIfNeeded(event, body_a, body_b);
        setImpulseScalingForTerrainContact(event, body_a, body_b);
    }

    if ((layer_a == ContactLayer::EntityWater &&
         body_b->getType() != RigidBody::Type::CharacterController) ||
        (layer_b == ContactLayer::EntityWater &&
         body_a->getType() != RigidBody::Type::CharacterController)) {
        body_a->onCollisionAdded();
        body_b->onCollisionAdded();
    }

    if (!should_process && m15(body_a, body_b)) {
        mMgr->addImpulseEntry(body_a, body_b);
    }
}

void EntityContactListener::collisionRemovedCallback(const hkpCollisionEvent& event) {
    auto* body_a = getRigidBody(*event.getBody(0));
    auto* body_b = getRigidBody(*event.getBody(1));

    handleCollisionRemoved(event, body_a, body_b);
    removeViscousSurfaceModifierAndCollision(event, body_a, body_b);
    removeMassChangerModifier(event, body_a, body_b);
}

bool EntityContactListener::m15(RigidBody* body_a, RigidBody* body_b) {
    if (body_a->isEntityMotionFlag4Off() && body_b->isEntityMotionFlag4Off() &&
        (body_a->getMaxImpulse() >= 0 || body_b->getMaxImpulse() >= 0)) {
        return true;
    }

    if (body_a->isEntityMotionFlag8On() || body_b->isEntityMotionFlag8On()) {
        return true;
    }

    return false;
}

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

// TODO: rename
static bool unkLayerCheck(const RigidBody* body_a, const RigidBody* body_b, ContactLayer layer_a,
                          ContactLayer layer_b) {
    if (layer_a.value() == ContactLayer::EntityPlayer ||
        layer_a.value() == ContactLayer::EntityNPC) {
        switch (layer_b.value()) {
        case ContactLayer::EntityObject:
        case ContactLayer::EntityGroundObject:
        case ContactLayer::EntityTree:
            if (!body_b->hasFlag(RigidBody::Flag::_400000))
                return true;
            break;
        case ContactLayer::EntityPlayer:
        case ContactLayer::EntityNPC:
            return true;
        default:
            break;
        }
    }

    if (layer_b.value() == ContactLayer::EntityPlayer ||
        layer_b.value() == ContactLayer::EntityNPC) {
        switch (layer_a.value()) {
        case ContactLayer::EntityObject:
        case ContactLayer::EntityGroundObject:
        case ContactLayer::EntityTree:
            if (!body_a->hasFlag(RigidBody::Flag::_400000))
                return true;
            break;
        default:
            break;
        }
    }

    return false;
}

bool EntityContactListener::contactPointCallbackImpl(u32 ignored_layers_a, u32 ignored_layers_b,
                                                     RigidBody* body_a, RigidBody* body_b,
                                                     ContactLayer layer_a, ContactLayer layer_b,
                                                     const hkpContactPointEvent& event) {
    if (shouldProcessEntityContact(ignored_layers_a, ignored_layers_b, layer_a, layer_b) ||
        (_91 && unkLayerCheck(body_a, body_b, layer_a, layer_b))) {
        disableContact(event);

        if (event.m_type == hkpContactPointEvent::TYPE_MANIFOLD &&
            (layer_a == ContactLayer::EntityWater || layer_b == ContactLayer::EntityWater)) {
            clearCallbackDelay(event);
        }

        return false;
    }

    if (isContactDisabled(event)) {
        auto* constraint = event.m_contactMgr->getConstraintInstance();
        if (constraint == nullptr ||
            constraint->getData()->getType() != hkpConstraintData::CONSTRAINT_TYPE_CONTACT ||
            !(constraint->getUserData() & 0x10000)) {
            // Clear the contact disabled flag.
            enableContact(event);
        }
    }
    return true;
}

void EntityContactListener::m11(const hkpContactPointEvent& event,
                                const RigidBodyCollisionMasks& masks_a,
                                const RigidBodyCollisionMasks& masks_b, RigidBody* body_a,
                                RigidBody* body_b) {
    auto* hk_point_properties = event.m_contactPointProperties;

    const MaterialMask mat_mask_a{masks_a.material_mask};
    const MaterialMask mat_mask_b{masks_b.material_mask};
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

KSYS_ALWAYS_INLINE static bool needsMagneMassScaling(const hkpCollisionEvent& event,
                                                     RigidBody* body_a, RigidBody* body_b) {
    if (body_a->getMotionType() != MotionType::Dynamic ||
        body_b->getMotionType() != MotionType::Dynamic) {
        return false;
    }

    if (body_a->getEntityMotionAccessor() == nullptr ||
        body_b->getEntityMotionAccessor() == nullptr) {
        return false;
    }

    if (body_a->getEntityMotionAccessor()->getContactFlags().isOff(ContactFlag::_1) &&
        body_b->getEntityMotionAccessor()->getContactFlags().isOff(ContactFlag::_1)) {
        return false;
    }

    if (!hasEntityWithMotionFlag80(event))
        return false;

    return body_a->getMagneMassScalingFactor() >= 0 && body_b->getMagneMassScalingFactor() >= 0;
}

static void updateMotionAccessorFlagsForMagneMassScaling(RigidBody* body_a, RigidBody* body_b) {
    // Set flag 1 and reset flag 2.
    body_a->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_1);
    body_b->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_1);

    body_a->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_2);
    body_b->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_2);
}

void EntityContactListener::setMagneMassScalingForContactIfNeeded(const hkpCollisionEvent& event,
                                                                  RigidBody* body_a,
                                                                  RigidBody* body_b) {
    if (!System::instance()->getEntityContactListenerField90())
        return;

    if (!needsMagneMassScaling(event, body_a, body_b))
        return;

    updateMotionAccessorFlagsForMagneMassScaling(body_a, body_b);
    setMagneMassScalingForContact(event, body_a, body_b);
}

void EntityContactListener::setImpulseScalingForTerrainContact(const hkpCollisionEvent& event,
                                                               RigidBody* body_a,
                                                               RigidBody* body_b) {
    if (body_a->getType() != RigidBody::Type::TerrainHeightField &&
        body_b->getType() != RigidBody::Type::TerrainHeightField) {
        return;
    }

    auto* body1 = body_a->getType() == RigidBody::Type::TerrainHeightField ? body_a : body_b;
    auto* body2 = body1 == body_a ? body_b : body_a;

    if (body2->getType() != RigidBody::Type::CharacterController ||
        int(body1->getContactLayer()) != ContactLayer::EntityGround) {
        return;
    }

    auto* height_field_body = sead::DynamicCast<TerrainHeightFieldRigidBody>(body1);
    if (!height_field_body || !height_field_body->getD8())
        return;

    [[maybe_unused]] auto* constraint = event.m_contactMgr->getConstraintInstance();
    hkpResponseModifier::setImpulseScalingForContact(event.m_contactMgr, body_a->getHkBody(),
                                                     body_b->getHkBody(),
                                                     *event.getSimulationIsland(), 15.0, 25.0);
}

static bool removeViscousSurfaceModifier(const hkpCollisionEvent& event) {
    constexpr auto type = hkpConstraintAtom::TYPE_MODIFIER_VISCOUS_SURFACE;
    auto* constraint = event.m_contactMgr->getConstraintInstance();
    if (!hkpWorldConstraintUtil::findModifier(constraint, type)) {
        return false;
    }

    auto* island = event.getSimulationIsland();
    hkpWorldConstraintUtil::removeAndDeleteModifier(constraint, *island, type);

    if (constraint &&
        constraint->getData()->getType() == hkpConstraintData::CONSTRAINT_TYPE_CONTACT) {
        // TODO: add named constants for this flag?
        constraint->m_userData &= ~1;
    }

    return true;
}

inline void EntityContactListener::removeViscousSurfaceModifierAndCollision(
    const hkpCollisionEvent& event, RigidBody* body_a, RigidBody* body_b) {
    if (!removeViscousSurfaceModifier(event))
        return;

    const auto update_contact_flags = [](RigidBody* body) {
        if (!body->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_1)) {
            return;
        }

        if (body->isEntityMotionFlag80On())
            return;

        body->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_1);
        body->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_2);
        body->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_4);
    };

    update_contact_flags(body_a);
    update_contact_flags(body_b);
    body_a->onCollisionRemoved();
    body_b->onCollisionRemoved();
}

KSYS_ALWAYS_INLINE inline void
EntityContactListener::removeMassChangerModifier(const hkpCollisionEvent& event, RigidBody* body_a,
                                                 RigidBody* body_b) {
    constexpr auto type = hkpConstraintAtom::TYPE_MODIFIER_MASS_CHANGER;
    auto* constraint = event.m_contactMgr->getConstraintInstance();
    if (hkpWorldConstraintUtil::findModifier(constraint, type)) {
        auto* island = event.getSimulationIsland();
        hkpWorldConstraintUtil::removeAndDeleteModifier(constraint, *island, type);
    }

    const auto a_is_water_and_b_not_charctrl = [](RigidBody* a, RigidBody* b) {
        return a->getContactLayer() == ContactLayer::EntityWater &&
               b->getType() != RigidBody::Type::CharacterController;
    };

    if (a_is_water_and_b_not_charctrl(body_a, body_b) ||
        a_is_water_and_b_not_charctrl(body_b, body_a)) {
        body_a->onCollisionRemoved();
        body_b->onCollisionRemoved();
    }
}

inline void EntityContactListener::setMagneMassScalingForContact(const hkpCollisionEvent& event,
                                                                 RigidBody* body_a,
                                                                 RigidBody* body_b) {
    const auto factor_a = body_a->getMagneMassScalingFactor();
    const auto factor_b = body_b->getMagneMassScalingFactor();

    body_a->onCollisionAdded();
    body_b->onCollisionAdded();

    const auto mass_a = body_a->getMass();
    const auto mass_b = body_b->getMass();

    const auto* heavier_body = (mass_a < mass_b) ? body_b : body_a;
    const auto* lighter_body = (mass_a < mass_b) ? body_a : body_b;

    const auto heavier_factor = (mass_a < mass_b) ? factor_b : factor_a;
    const auto lighter_factor = (mass_a < mass_b) ? factor_a : factor_b;

    const auto effective_mass1 = lighter_body->getMass() * heavier_factor;
    const auto effective_mass2 = heavier_body->getMass() * lighter_factor;

    hkVector4f mass_ratio;
    mass_ratio.setAll(effective_mass1 / effective_mass2);

    hkpResponseModifier::setInvMassScalingForContact(event.m_contactMgr, lighter_body->getHkBody(),
                                                     *event.getSimulationIsland(), mass_ratio);

    if (auto* constraint = event.m_contactMgr->getConstraintInstance()) {
        if (constraint->getData()->getType() == hkpConstraintData::CONSTRAINT_TYPE_CONTACT)
            constraint->m_userData |= 1;
    }
}

static void updateMotionFlagsAtEndOfStep(const hkpCollisionEvent& event, RigidBody* body_a,
                                         RigidBody* body_b) {
    const auto update_flags1 = [](RigidBody* a, RigidBody* b) {
        if (!a->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_2))
            return false;
        if (!b->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_4))
            return false;

        a->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_1);
        a->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_2);
        a->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_4);
        return true;
    };

    const auto update_flags2 = [](RigidBody* a, RigidBody* b) {
        if (!a->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_2))
            return false;
        if (b->isEntityMotionFlag80On())
            return false;
        if (!b->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_1))
            return false;

        b->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_1);
        b->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_2);
        return true;
    };

    const auto update_flags3 = [](RigidBody* a, RigidBody* b) {
        if (!a->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_1))
            return false;
        if (!b->getEntityMotionAccessor()->getContactFlags().isOff(ContactFlag::_1))
            return false;

        b->getEntityMotionAccessor()->getContactFlags().set(ContactFlag::_1);
        b->getEntityMotionAccessor()->getContactFlags().reset(ContactFlag::_2);
        return true;
    };

    const auto update_flags4 = [](RigidBody* body) {
        if (!body->getEntityMotionAccessor()->getContactFlags().isOn(ContactFlag::_4))
            return false;
        if (body->isEntityMotionFlag80On())
            return false;
        if (body->x_105())
            return false;

        body->getEntityMotionAccessor()->getContactFlags() = ContactFlag::_1;
        return true;
    };

    bool updated1 = false;
    updated1 |= update_flags1(body_a, body_b);
    updated1 |= update_flags1(body_b, body_a);

    if (!updated1) {
        bool updated2 = false;
        updated2 |= update_flags2(body_a, body_b);
        updated2 |= update_flags2(body_b, body_a);

        if (updated2) {
            removeViscousSurfaceModifier(event);
        } else {
            update_flags3(body_a, body_b);
            update_flags3(body_b, body_a);
        }
    }

    update_flags4(body_a);
    update_flags4(body_b);
}

// NON_MATCHING: branching (body_a->getEntityMotionAccessor() call not merged)
bool EntityContactListener::regularContactPointCallback(const hkpContactPointEvent& event,
                                                        RigidBody* body_a, RigidBody* body_b,
                                                        sead::SafeArray<u32, 2>*) {
    if (event.m_type == hkpContactPointEvent::TYPE_MANIFOLD_AT_END_OF_STEP) {
        auto* constraint = event.m_contactMgr->getConstraintInstance();

        auto* modifier = hkpWorldConstraintUtil::findModifier(
            constraint, hkpConstraintAtom::TYPE_MODIFIER_VISCOUS_SURFACE);

        const bool field90 = System::instance()->getEntityContactListenerField90();

        if (modifier && constraint->getUserData() & 1) {
            clearCallbackDelay(event);

            if (field90 && hasEntityWithMotionFlag80(event)) {
                updateMotionFlagsAtEndOfStep(event, body_a, body_b);
            } else {
                body_a->getEntityMotionAccessor()->getContactFlags().makeAllZero();
                body_b->getEntityMotionAccessor()->getContactFlags().makeAllZero();
                removeViscousSurfaceModifier(event);
            }
        } else if (field90 && needsMagneMassScaling(event, body_a, body_b) &&
                   !shouldProcessEntityContact(body_a, body_b)) {
            updateMotionAccessorFlagsForMagneMassScaling(body_a, body_b);
            setMagneMassScalingForContact(event, body_a, body_b);
        }
    }

    sead::SafeArray<u32, 2> material_masks;
    bool result =
        ContactListener::regularContactPointCallback(event, body_a, body_b, &material_masks);

    if (event.m_contactPointProperties->m_flags & hkpContactPointProperties::CONTACT_IS_NEW &&
        m15(body_a, body_b)) {
        sead::Vector3f position, normal;
        storeToVec3(&position, event.m_contactPoint->getPosition());
        storeToVec3(&normal, event.m_contactPoint->getSeparatingNormal());
        if (body_a->isEntityMotionFlag40On() || body_b->isEntityMotionFlag40On()) {
            mMgr->addImpulseEntry(body_a, body_b);
        }

        mMgr->setImpulseEntryContactInfo(body_a, body_b, position, normal, material_masks[0],
                                         material_masks[1]);
    }

    return result;
}

}  // namespace ksys::phys
