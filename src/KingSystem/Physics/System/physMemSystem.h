#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class ContactMgr;
class GroupFilter;
class RigidBody;
class RigidContactPoints;
class RigidContactPointsEx;
class SystemGroupHandler;

// FIXME: obviously incomplete. Also this should be moved to its own header
struct RigidBodyRequestMgr {
    void sub_7100FA6C8C(bool, RigidBody*);
};

class MemSystem {
    SEAD_SINGLETON_DISPOSER(MemSystem)
    MemSystem();
    virtual ~MemSystem();

public:
    GroupFilter* getGroupFilter(ContactLayerType type) const;
    ContactMgr* getContactMgr() const { return mContactMgr; }
    RigidBodyRequestMgr* getRigidBodyRequestMgr() const { return mRigidBodyRequestMgr; }

    RigidContactPoints* allocContactPoints(sead::Heap* heap, int num, const sead::SafeString& name,
                                           int a, int b, int c) const;
    void freeContactPoints(RigidContactPoints* points) const;
    void registerContactPoints(RigidContactPoints* points) const;
    void registerContactPointLayerPair(RigidContactPointsEx* points, ContactLayer layer1,
                                       ContactLayer layer2, bool enabled);

    void removeSystemGroupHandler(SystemGroupHandler* handler);

private:
    u8 _28[0x148 - 0x28];
    ContactMgr* mContactMgr;
    void* _150;
    void* _158;
    RigidBodyRequestMgr* mRigidBodyRequestMgr;
    u8 _168[0x480 - 0x168];
};
KSYS_CHECK_SIZE_NX150(MemSystem, 0x480);

}  // namespace ksys::phys
