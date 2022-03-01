#pragma once

#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>
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

    void registerRigidBody(RigidBody* body);

    void contactPointCallback(const hkpContactPointEvent& event) override;
    void collisionAddedCallback(const hkpCollisionEvent& event) override;
    void collisionRemovedCallback(const hkpCollisionEvent& event) override;
    void contactPointAddedCallback(hkpContactPointAddedEvent& event) override {}
    void contactPointRemovedCallback(hkpContactPointRemovedEvent& event) override {}
    void contactProcessCallback(hkpContactProcessEvent& event) override {}

protected:
    virtual bool characterControlContactPointCallback(u32 ignored_layers_a, u32 ignored_layers_b,
                                                      RigidBody* body_a, RigidBody* body_b,
                                                      ContactLayer layer_a, ContactLayer layer_b,
                                                      const hkpContactPointEvent& event);

    virtual void m11() {}

    virtual void handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                      RigidBody* body_b);

    void handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                RigidBody* body_b);

    virtual bool manifoldContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                              RigidBody* body_b);

    /// @param out_material_masks [Optional] Pass this to get the materials of the rigid bodies.
    virtual bool regularContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                             RigidBody* body_b,
                                             sead::SafeArray<MaterialMask, 2>* out_material_masks);

    virtual u32 m15() { return 0; }

    std::pair<int, int> convertToRelativeLayer(ContactLayer layer1, ContactLayer layer2) const {
        return {layer1 - int(mLayerBase), layer2 - int(mLayerBase)};
    }

private:
    struct TrackedContactPointLayer {
        LayerContactPointInfo* info;
        ContactLayer layer;
        bool enabled;
    };

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
    u16 _90{};
    bool _92{};
};

}  // namespace ksys::phys
