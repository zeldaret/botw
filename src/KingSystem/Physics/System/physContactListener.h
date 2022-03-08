#pragma once

#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include <utility>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

class ContactLayerCollisionInfo;
class ContactMgr;
class LayerContactPointInfo;
class RigidBody;
struct RigidBodyCollisionMasks;

class ContactListener : public hkpContactListener, public sead::hostio::Node {
    SEAD_RTTI_BASE(ContactListener)
public:
    ContactListener(ContactMgr* mgr, ContactLayerType layer_type, int layer_count);
    ~ContactListener() override;

    void init(sead::Heap* heap);
    void clearTable();

    bool areContactsTrackedForLayerPair(u32 rlayer_a, u32 rlayer_b) const;
    ContactLayerCollisionInfo* trackLayerPair(ContactLayer layer_a, ContactLayer layer_b);
    ContactLayerCollisionInfo* getContactLayerCollisionInfo(u32 rlayer_a, u32 rlayer_b);

    void addLayerPairForContactPointInfo(LayerContactPointInfo* info, ContactLayer layer1,
                                         ContactLayer layer2, bool enabled);
    void removeLayerPairsForContactPointInfo(LayerContactPointInfo* info);
    void removeLayerPairForContactPointInfo(LayerContactPointInfo* info, ContactLayer layer1,
                                            ContactLayer layer2);

    void unregisterCollisionWithBody(RigidBody* body);

    void contactPointCallback(const hkpContactPointEvent& event) override;
    void collisionAddedCallback(const hkpCollisionEvent& event) override;
    void collisionRemovedCallback(const hkpCollisionEvent& event) override;
    void contactPointAddedCallback(hkpContactPointAddedEvent& event) override {}
    void contactPointRemovedCallback(hkpContactPointRemovedEvent& event) override {}
    void contactProcessCallback(hkpContactProcessEvent& event) override {}

    static void clearCallbackDelay(const hkpContactPointEvent& event) {
        event.m_contactMgr->m_contactPointCallbackDelay = 0;
    }

    static void enableContact(const hkpContactPointEvent& event) {
        event.m_contactPointProperties->m_flags &= ~hkpContactPointProperties::CONTACT_IS_DISABLED;
    }

    static void disableContact(const hkpContactPointEvent& event) {
        event.m_contactPointProperties->m_flags |= hkpContactPointProperties::CONTACT_IS_DISABLED;
    }

    static bool isContactDisabled(const hkpContactPointEvent& event) {
        return event.m_contactPointProperties->m_flags &
               hkpContactPointProperties::CONTACT_IS_DISABLED;
    }

protected:
    struct TrackedContactPointLayer {
        LayerContactPointInfo* info;
        ContactLayer layer;
        bool do_not_delay_callback;
    };

    virtual bool contactPointCallbackImpl(u32 ignored_layers_a, u32 ignored_layers_b,
                                          RigidBody* body_a, RigidBody* body_b,
                                          ContactLayer layer_a, ContactLayer layer_b,
                                          const hkpContactPointEvent& event);

    virtual void m11(const hkpContactPointEvent& event, const RigidBodyCollisionMasks& masks_a,
                     const RigidBodyCollisionMasks& masks_b, RigidBody* body_a, RigidBody* body_b) {
    }

    virtual void handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                      RigidBody* body_b);

    void handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                RigidBody* body_b);

    virtual bool manifoldContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                              RigidBody* body_b);

    /// @param out_material_masks [Optional] Pass this to get the materials of the rigid bodies.
    virtual bool regularContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                             RigidBody* body_b,
                                             sead::SafeArray<u32, 2>* out_material_masks);

    virtual bool m15(RigidBody* body_a, RigidBody* body_b) { return false; }

    /// Record a contact point in the ContactPointInfo instances of the bodies (if applicable).
    int notifyContactPointInfo(RigidBody* body_a, RigidBody* body_b, ContactLayer layer_a,
                               ContactLayer layer_b, const RigidBodyCollisionMasks& masks_a,
                               const RigidBodyCollisionMasks& masks_b,
                               const hkpContactPointEvent& event, bool callbacks_ok);

    /// Record a contact point in the specified LayerContactPointInfo (if applicable).
    void notifyLayerContactPointInfo(const TrackedContactPointLayer& tracked_layer, int,
                                     RigidBody* body_a, RigidBody* body_b, ContactLayer layer_a,
                                     ContactLayer layer_b, u32 material_a, u32 material_b,
                                     const hkpContactPointEvent& event);

    std::pair<int, int> convertToRelativeLayer(ContactLayer layer1, ContactLayer layer2) const {
        return {layer1 - int(mLayerBase), layer2 - int(mLayerBase)};
    }

protected:
    ContactMgr* mMgr{};
    ContactLayerType mLayerType{};
    u32 mLayerBase{};
    sead::Buffer<sead::Buffer<sead::FixedObjArray<TrackedContactPointLayer, 8>>>
        mTrackedContactPointLayers;
    sead::Buffer<sead::Buffer<ContactLayerCollisionInfo*>> mCollisionInfoPerLayerPair;
    u8* mTrackedLayers{};
    u32 mTrackedLayersBufferSize{};
    u32 mLayerCount{};
    sead::CriticalSection mCS;
    bool _90 = false;
    bool _91 = false;
    bool mDisableContactPointInfoNotifications = false;
};

}  // namespace ksys::phys
