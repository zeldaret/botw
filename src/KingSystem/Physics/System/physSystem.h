#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

class hkpWorld;

namespace ksys::phys {

class CollisionInfo;
class ContactLayerCollisionInfo;
class ContactLayerCollisionInfoGroup;
class ContactMgr;
class ContactPointInfo;
class GroupFilter;
class LayerContactPointInfo;
class MaterialTable;
class RayCastForRequest;
class RigidBody;
class RigidBodyRequestMgr;
class StaticCompoundMgr;
class SystemData;
class SystemGroupHandler;

enum class IsIndoorStage {
    No,
    Yes,
};

enum class LowPriority : bool { Yes = true, No = false };
enum class OnlyLockIfNeeded : bool { Yes = true, No = false };

class System {
    SEAD_SINGLETON_DISPOSER(System)
    System();
    virtual ~System();

public:
    float get64() const { return _64; }
    float getTimeFactor() const { return mTimeFactor; }
    ContactMgr* getContactMgr() const { return mContactMgr; }
    StaticCompoundMgr* getStaticCompoundMgr() const { return mStaticCompoundMgr; }
    RigidBodyRequestMgr* getRigidBodyRequestMgr() const { return mRigidBodyRequestMgr; }
    SystemData* getSystemData() const { return mSystemData; }
    MaterialTable* getMaterialTable() const { return mMaterialTable; }

    bool isPaused() const;

    void initSystemData(sead::Heap* heap);

    ContactPointInfo* allocContactPointInfo(sead::Heap* heap, int num, const sead::SafeString& name,
                                            int a, int b, int c) const;
    void freeContactPointInfo(ContactPointInfo* info) const;

    LayerContactPointInfo* allocLayerContactPointInfo(sead::Heap* heap, int num, int num2,
                                                      const sead::SafeString& name, int a, int b,
                                                      int c) const;
    void freeLayerContactPointInfo(LayerContactPointInfo* info) const;

    void registerContactPointInfo(ContactPointInfo* info) const;
    // 0x000000710121696c
    void registerCollisionInfo(CollisionInfo* info) const;
    // 0x0000007101216974
    void registerContactPointLayerPair(LayerContactPointInfo* info, ContactLayer layer1,
                                       ContactLayer layer2, bool enabled);

    // 0x00000071012169a4
    CollisionInfo* allocCollisionInfo(sead::Heap* heap, const sead::SafeString& name) const;
    // 0x00000071012169ac
    void freeCollisionInfo(CollisionInfo* info) const;

    // 0x00000071012169b4
    ContactLayerCollisionInfoGroup*
    makeContactLayerCollisionInfoGroup(sead::Heap* heap, ContactLayer layer, int capacity,
                                       const sead::SafeString& name);
    // 0x00000071012169c0
    void freeContactLayerCollisionInfoGroup(ContactLayerCollisionInfoGroup* group);
    // 0x00000071012169c8
    ContactLayerCollisionInfo* trackLayerPair(ContactLayer layer_a, ContactLayer layer_b);

    // 0x0000007101216a20
    void removeRigidBodyFromContactSystem(RigidBody* body);

    // 0x000000710121686c
    SystemGroupHandler* addSystemGroupHandler(ContactLayerType layer_type, int free_list_idx = 0);
    // 0x0000007101215b68
    void removeSystemGroupHandler(SystemGroupHandler* handler);

    hkpWorld* getHavokWorld(ContactLayerType type) const;

    // 0x0000007101215754
    void lockWorld(ContactLayerType type, const char* description = nullptr, int b = 0,
                   OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No);
    // 0x0000007101215784
    void unlockWorld(ContactLayerType type, const char* description = nullptr, int b = 0,
                     OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No);

    // 0x0000007101216ac8
    GroupFilter* getGroupFilter(ContactLayerType type) const;

    // 0x0000007101216ae8
    RayCastForRequest* allocRayCastRequest(SystemGroupHandler* group_handler = nullptr,
                                           GroundHit ground_hit = GroundHit::HitAll);

    // TODO: rename
    // 0x0000007101216c60
    void setEntityContactListenerField90(bool value);
    // 0x0000007101216c74
    bool getEntityContactListenerField90() const;

    // 0x0000007101216ca4
    bool isActorSystemIdle() const;

    // 0x0000007101216800
    void setEntityContactListenerField91(bool value);
    // 0x0000007101216814
    bool getEntityContactListenerField91() const;

    // 0x000000710121682c
    void incrementWorldUnkCounter(ContactLayerType layer_type);
    // 0x000000710121684c
    void decrementWorldUnkCounter(ContactLayerType layer_type);

    // 0x0000007101216cec
    sead::Heap* getPhysicsTempHeap(LowPriority low_priority) const;

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
    StaticCompoundMgr* mStaticCompoundMgr;
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

class ScopedWorldLock {
public:
    explicit ScopedWorldLock(ContactLayerType type, const char* description = nullptr, int unk = 0,
                             OnlyLockIfNeeded only_lock_if_needed = OnlyLockIfNeeded::No)
        : mType(type), mDescription(description), mUnk(unk),
          mOnlyLockIfNeeded(only_lock_if_needed) {
        System::instance()->lockWorld(mType, mDescription, mUnk, mOnlyLockIfNeeded);
    }

    ~ScopedWorldLock() {
        System::instance()->unlockWorld(mType, mDescription, mUnk, mOnlyLockIfNeeded);
    }

    ScopedWorldLock(const ScopedWorldLock&) = delete;
    auto operator=(const ScopedWorldLock&) = delete;

private:
    ContactLayerType mType;
    const char* mDescription;
    int mUnk;
    OnlyLockIfNeeded mOnlyLockIfNeeded;
};

}  // namespace ksys::phys
