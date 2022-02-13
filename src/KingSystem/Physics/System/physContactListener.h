#pragma once

#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactListener.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class ContactMgr;
class RigidBody;

struct ContactUnk1 {
    ContactUnk1(u32 layer);
    virtual ~ContactUnk1();

    u8 _8[0x68];
};

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
    void contactPointAddedCallback(hkpContactPointAddedEvent& event) override;
    void contactPointRemovedCallback(hkpContactPointRemovedEvent& event) override;
    void contactProcessCallback(hkpContactProcessEvent& event) override;

    virtual void m10();
    virtual void m11() {}
    virtual void handleCollisionAdded(const hkpCollisionEvent& event, RigidBody* bodyA,
                                      RigidBody* bodyB);
    virtual void m13();
    virtual void m14();
    virtual u32 m15() { return 0; }

protected:
    void handleCollisionRemoved(const hkpCollisionEvent& event, RigidBody* bodyA, RigidBody* bodyB);

private:
    struct Unk1 {
        void* _0;
        void* _8;
    };

    ContactMgr* mMgr{};
    ContactLayerType mLayerType{};
    u32 mLayerBase{};
    sead::Buffer<sead::Buffer<sead::FixedObjArray<Unk1, 8>>> _20;
    sead::Buffer<sead::Buffer<ContactUnk1*>> _30;
    void* _40{};
    u32 _48{};
    u32 mLayerCount{};
    sead::CriticalSection mCS;
    u16 _90{};
    bool _92{};
};

}  // namespace ksys::phys
