#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class ContactMgr;
class GroupFilter;
class MaterialTable;
class RigidBody;
class RigidContactPoints;
class RigidContactPointsEx;
class SystemData;
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
    SystemData* getSystemData() const { return mSystemData; }
    MaterialTable* getMaterialTable() const { return mMaterialTable; }

    RigidContactPoints* allocContactPoints(sead::Heap* heap, int num, const sead::SafeString& name,
                                           int a, int b, int c) const;
    void freeContactPoints(RigidContactPoints* points) const;
    RigidContactPointsEx* allocContactPointsEx(sead::Heap* heap, int num, int num2,
                                               const sead::SafeString& name, int a, int b,
                                               int c) const;
    void freeContactPointsEx(RigidContactPointsEx* points) const;
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
    void* _168;
    void* mRigidBodyDividedMeshShapeMgr;
    SystemData* mSystemData;
    MaterialTable* mMaterialTable;
    u8 _188[0x480 - 0x188];
};
KSYS_CHECK_SIZE_NX150(MemSystem, 0x480);

}  // namespace ksys::phys
