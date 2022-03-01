#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class CollisionInfo;
class ContactMgr;
class GroupFilter;
class MaterialTable;
class RigidBody;
class RigidBodyRequestMgr;
class ContactPointInfo;
class ContactPointInfoEx;
class SystemData;
class SystemGroupHandler;

enum class IsIndoorStage {
    No,
    Yes,
};

class System {
    SEAD_SINGLETON_DISPOSER(System)
    System();
    virtual ~System();

public:
    float get64() const { return _64; }
    float getTimeFactor() const { return mTimeFactor; }
    GroupFilter* getGroupFilter(ContactLayerType type) const;
    ContactMgr* getContactMgr() const { return mContactMgr; }
    RigidBodyRequestMgr* getRigidBodyRequestMgr() const { return mRigidBodyRequestMgr; }
    SystemData* getSystemData() const { return mSystemData; }
    MaterialTable* getMaterialTable() const { return mMaterialTable; }

    bool isPaused() const;

    void initSystemData(sead::Heap* heap);

    ContactPointInfo* allocContactPointInfo(sead::Heap* heap, int num, const sead::SafeString& name,
                                            int a, int b, int c) const;
    void freeContactPointInfo(ContactPointInfo* info) const;

    ContactPointInfoEx* allocContactPointsEx(sead::Heap* heap, int num, int num2,
                                             const sead::SafeString& name, int a, int b,
                                             int c) const;
    void freeContactPointInfoEx(ContactPointInfoEx* info) const;

    void registerContactPointInfo(ContactPointInfo* info) const;
    // 0x000000710121696c
    void registerCollisionInfo(CollisionInfo* info) const;
    // 0x0000007101216974
    void registerContactPointLayerPair(ContactPointInfoEx* info, ContactLayer layer1,
                                       ContactLayer layer2, bool enabled);

    // 0x00000071012169a4
    CollisionInfo* allocCollisionInfo(sead::Heap* heap, const sead::SafeString& name) const;
    // 0x00000071012169ac
    void freeCollisionInfo(CollisionInfo* info) const;

    // 0x0000007101216a20
    void registerRigidBodyForContactSystem(RigidBody* body);

    void removeSystemGroupHandler(SystemGroupHandler* handler);

    void lockWorld(ContactLayerType type, void* a = nullptr, int b = 0, bool c = false);
    void unlockWorld(ContactLayerType type, void* a = nullptr, int b = 0, bool c = false);

private:
    u8 _28[0x64 - 0x28];
    float _64 = 1.0 / 30.0;
    float _68 = 1.0 / 30.0;
    float _6c = 1.0;
    float _70 = 1.0 / 30.0;
    float mTimeFactor{};
    u8 _78[0xa8 - 0x78];
    sead::CriticalSection mCS;
    void* _e8{};
    void* _f0{};
    GroupFilter* mEntityGroupFilter{};
    GroupFilter* mSensorGroupFilter{};
    sead::FixedPtrArray<GroupFilter, 2> mGroupFilters;
    // FIXME: type
    sead::FixedPtrArray<void*, 2> _128;
    ContactMgr* mContactMgr;
    void* _150;
    void* _158;
    RigidBodyRequestMgr* mRigidBodyRequestMgr;
    void* _168;
    void* mRigidBodyDividedMeshShapeMgr;
    SystemData* mSystemData;
    MaterialTable* mMaterialTable;
    void* _188{};
    void* _190{};
    void* _198{};
    void* _1a0{};
    sead::Heap* mPhysicsSystemHeap{};
    sead::Heap* mDebugHeap{};
    sead::Heap* mPhysicsTempDefaultHeap{};
    sead::Heap* mPhysicsTempLowHeap{};
    u8 _1c8[0x480 - 0x1c8];
};
KSYS_CHECK_SIZE_NX150(System, 0x480);

}  // namespace ksys::phys
