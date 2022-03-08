#pragma once

#include "KingSystem/Physics/System/physContactListener.h"

class hkpCdBody;

namespace ksys::phys {

class EntityContactListener : public ContactListener {
    SEAD_RTTI_OVERRIDE(EntityContactListener, ContactListener)
public:
    static EntityContactListener* make(ContactMgr* mgr, sead::Heap* heap);

    ~EntityContactListener() override;
    void collisionAddedCallback(const hkpCollisionEvent& event) override;
    void collisionRemovedCallback(const hkpCollisionEvent& event) override;

    static bool isObjectOrGroundOrNPCOrTree(const RigidBody& body);
    static bool isObjectOrGroundOrNPCOrTree(const hkpCdBody& cd_body);

protected:
    EntityContactListener(ContactMgr* mgr, sead::Heap* heap);

    bool contactPointCallbackImpl(u32 ignored_layers_a, u32 ignored_layers_b, RigidBody* body_a,
                                  RigidBody* body_b, ContactLayer layer_a, ContactLayer layer_b,
                                  const hkpContactPointEvent& event) override;

    void m11(const hkpContactPointEvent& event, const RigidBodyCollisionMasks& masks_a,
             const RigidBodyCollisionMasks& masks_b, RigidBody* body_a, RigidBody* body_b) override;

    bool regularContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                     RigidBody* body_b,
                                     sead::SafeArray<u32, 2>* out_material_masks) override;

    bool m15(RigidBody* body_a, RigidBody* body_b) override;

private:
    void setMagneMassScalingForContactIfNeeded(const hkpCollisionEvent& event, RigidBody* body_a,
                                               RigidBody* body_b);

    void setImpulseScalingForTerrainContact(const hkpCollisionEvent& event, RigidBody* body_a,
                                            RigidBody* body_b);

    void removeViscousSurfaceModifierAndCollision(const hkpCollisionEvent& event, RigidBody* body_a,
                                                  RigidBody* body_b);

    void removeMassChangerModifier(const hkpCollisionEvent& event, RigidBody* body_a,
                                   RigidBody* body_b);

    void setMagneMassScalingForContact(const hkpCollisionEvent& event, RigidBody* body_a,
                                       RigidBody* body_b);
};

}  // namespace ksys::phys
