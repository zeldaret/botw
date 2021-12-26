#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class ContactMgr;
class GroupFilter;
class RigidBody;
class SystemGroupHandler;

// FIXME: obviously incomplete. Also this should be moved to its own header
struct RigidBodyRequestMgr {
    void sub_7100FA6C8C(bool, RigidBody*);
};

class MemSystem {
    SEAD_SINGLETON_DISPOSER(MemSystem)
public:
    GroupFilter* getGroupFilter(ContactLayerType type) const;
    ContactMgr* getContactMgr() const { return mContactMgr; }
    RigidBodyRequestMgr* getRigidBodyRequestMgr() const { return mRigidBodyRequestMgr; }

    void removeSystemGroupHandler(SystemGroupHandler* handler);

private:
    u8 _20[0x148 - 0x20];
    ContactMgr* mContactMgr;
    void* _150;
    void* _158;
    RigidBodyRequestMgr* mRigidBodyRequestMgr;
    u8 _168[0x480 - 0x168];
};
KSYS_CHECK_SIZE_NX150(MemSystem, 0x480);

}  // namespace ksys::phys
