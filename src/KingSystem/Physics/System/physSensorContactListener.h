#pragma once

#include "KingSystem/Physics/System/physContactListener.h"

namespace ksys::phys {

class SensorContactListener : public ContactListener {
    SEAD_RTTI_OVERRIDE(SensorContactListener, ContactListener)
public:
    static SensorContactListener* make(ContactMgr* mgr, sead::Heap* heap);

    ~SensorContactListener() override;

protected:
    explicit SensorContactListener(ContactMgr* mgr);

    void handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                              RigidBody* body_b) override;
    bool manifoldContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                      RigidBody* body_b) override;
    bool regularContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                     RigidBody* body_b,
                                     sead::SafeArray<u32, 2>* out_material_masks) override;
};

}  // namespace ksys::phys
