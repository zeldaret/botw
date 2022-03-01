#pragma once

#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class ContactLayerCollisionInfo;
class ContactMgr;
class RigidBody;

class ContactListener : public hkpContactListener, public sead::hostio::Node {
    SEAD_RTTI_BASE(ContactListener)
public:
    ContactListener(ContactMgr* mgr, ContactLayerType layer_type, int layer_count);
    ~ContactListener() override;

    void init(sead::Heap* heap);
    void clearTable();

    void contactPointCallback(const hkpContactPointEvent& event) override;
    void collisionAddedCallback(const hkpCollisionEvent& event) override;
    void collisionRemovedCallback(const hkpCollisionEvent& event) override;
    void contactPointAddedCallback(hkpContactPointAddedEvent& event) override {}
    void contactPointRemovedCallback(hkpContactPointRemovedEvent& event) override {}
    void contactProcessCallback(hkpContactProcessEvent& event) override {}

protected:
    virtual void characterControlContactPointCallback(u32 ignored_layers_a, u32 ignored_layers_b,
                                                      RigidBody* body_a, RigidBody* body_b,
                                                      ContactLayer layer_a, ContactLayer layer_b,
                                                      const hkpContactPointEvent& event);

    virtual void m11() {}

    virtual void handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* body_a,
                                      RigidBody* body_b);

    void handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* body_a,
                                RigidBody* body_b);

    virtual void manifoldContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                              RigidBody* body_b);

    virtual void regularContactPointCallback(const hkpContactPointEvent& event, RigidBody* body_a,
                                             RigidBody* body_b, void* unk = nullptr);

    virtual u32 m15() { return 0; }

private:
    struct Unk1 {
        void* _0;
        void* _8;
    };

    ContactMgr* mMgr{};
    ContactLayerType mLayerType{};
    u32 mLayerBase{};
    sead::Buffer<sead::Buffer<sead::FixedObjArray<Unk1, 8>>> _20;
    sead::Buffer<sead::Buffer<ContactLayerCollisionInfo*>> mCollisionInfoPerLayerPair;
    void* _40{};
    u32 _48{};
    u32 mLayerCount{};
    sead::CriticalSection mCS;
    u16 _90{};
    bool _92{};
};

}  // namespace ksys::phys
